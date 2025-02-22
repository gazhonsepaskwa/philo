/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:11:22 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/20 12:11:22 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include "utils/utils.h"
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int8_t	err(char *msg)
{
	printf("\033[31m%s\033[0m\n", msg);
	return (1);
}

bool check_death(t_table *t, size_t	p)
{
	struct timeval	tv;
	long long		now;
	bool			out;

	out = false;
	gettimeofday(&tv, NULL);
	now = ((long long)(tv.tv_sec) *1000) + (tv.tv_usec / 1000);
	pthread_mutex_lock(&t->philos_d[p]->lm_lock);
	if (now - t->philos_d[p]->last_meal >= t->death_time)
	{
		// debug
		pthread_mutex_lock(&t->print);
		printf("now : %lld | last_meal :%lld | diff : %lld", now, t->philos_d[p]->last_meal, (now - t->philos_d[p]->last_meal));
		pthread_mutex_unlock(&t->print);
		//debug

		out = true;
	}
	pthread_mutex_unlock(&t->philos_d[p]->lm_lock);
	return (out);
}

bool	philo_done(t_table *table)
{
	pthread_mutex_lock(&table->done_lock);
	if (table->done == table->philo_count)
	{
		pthread_mutex_unlock(&table->done_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&table->done_lock);
		return (false);
	}
}

void wait_end(t_table *table)
{
	size_t	p;
	bool	stop;

	stop = false;
	msleep((table->eat_time) + 1); // optimize the time ??
	while(!stop)
	{
		p = -1;
		msleep(1); // optimize the time
		while (++p < table->philo_count)
		{
			if (check_death(table, p))
			{
				status(table->philos_d[p], DIED);
				stop = true;
				break;
			}
		}
		if (stop == true || philo_done(table))
			break;
	}
	pthread_mutex_lock(&table->sim_s_lock);
	table->simstop = true;
	pthread_mutex_unlock(&table->sim_s_lock);
}

int	main(int ac, char **av)
{
	t_table	*table;

	if (!check_ok(ac, av))
		return (1);
	table = init(av);
	if (!table)
		return (err("Table init failed"));
	if (CUTE)
	{
		printf("┏━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━┳━━━━━━━━━━━━━━━━━━━┓\n");
		printf("┃ Elapsed time (in ms) ┃  id  ┃       state       ┃\n");
		printf("┣━━━━━━━━━━━━━━━━━━━━━━╋━━━━━━╋━━━━━━━━━━━━━━━━━━━┫\n");
	}
	if (!create_philos(table))
		return (err("Philo init failed"));
	wait_end(table);
	if (!join_philos(table))
		return (err("Philo join failed"));
	if (CUTE)
		printf("┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━┻━━━━━━━━━━━━━━━━━━━┛\n");
	return (0);
}
