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

bool	check_death(t_table *t, unsigned int p)
{
	bool			out;
	long long int	now;

	out = false;
	now = get_passed_ms(false);
	pthread_mutex_lock(&t->philos_d[p]->lm_lock);
	if (now - t->philos_d[p]->last_meal > t->death_time)
		out = true;
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

static void	stop_sim(t_table *table)
{
	pthread_mutex_lock(&table->sim_s_lock);
	table->simstop = true;
	pthread_mutex_unlock(&table->sim_s_lock);
}

unsigned int	wait_end(t_table *table)
{
	unsigned int	p;
	bool			stop;

	stop = false;
	msleep(1);
	while (!stop)
	{
		p = -1;
		while (++p < table->philo_count)
		{
			if (check_death(table, p))
			{
				stop = true;
				break ;
			}
		}
		if (stop == true || philo_done(table))
			break ;
		usleep(100);
	}
	stop_sim(table);
	if (stop)
		return (p + 1);
	return (-1);
}
