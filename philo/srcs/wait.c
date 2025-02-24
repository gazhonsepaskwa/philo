/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 09:19:09 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/24 09:19:09 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include "utils/utils.h"

bool check_death(t_table *t, size_t	p)
{
	bool			out;
	int		 		now;

	out = false;
	now = get_passed_ms(false);
	pthread_mutex_lock(&t->philos_d[p]->lm_lock);
	if (now - t->philos_d[p]->last_meal >= t->death_time)
	{
		// debug
		// pthread_mutex_lock(&t->print);
		// printf("now : %d | last_meal :%d | diff : %d", now, (int)t->philos_d[p]->last_meal, (int)(now - t->philos_d[p]->last_meal));
		// pthread_mutex_unlock(&t->print);
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
