/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   habit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:51:19 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/20 15:51:19 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"
#include "../utils/utils.h"
#include <sys/time.h>
#include <time.h>

bool sig_death(t_philo_data* d)
{
	pthread_mutex_lock(&d->t->sim_s_lock);
	if (d->t->simstop)
	{
		pthread_mutex_unlock(&d->t->sim_s_lock);
		return (true);
	}
	else
	{
		pthread_mutex_unlock(&d->t->sim_s_lock);
		return (false);
	}
}

bool	status(t_philo_data *data, char *msg)
{
	if (sig_death(data))
		return (true);
	pthread_mutex_lock(&data->t->print);
	if (CUTE)
		printf("┃ %-21lld┃ %-4d ┃ %-18s┃\n", get_passed_ms(false), data->id, msg);
	else
		printf("%lld %d %s\n", get_passed_ms(false), data->id, msg);
	pthread_mutex_unlock(&data->t->print);
	return(false);
}

void	lock_forks(t_philo_data *d, bool *stop)
{
	if (d->id % 2)
		pthread_mutex_lock(&(d->t->forks[d->id - 1]));
	else
		pthread_mutex_lock(&(d->t->forks[(d->id) % d->t->philo_count]));
	*stop = status(d , FORK);
	if (d->id % 2)
		pthread_mutex_lock(&(d->t->forks[(d->id) % d->t->philo_count]));
	else
		pthread_mutex_lock(&(d->t->forks[d->id - 1]));
	*stop = *stop || status(d , FORK);

}

bool	habit_eat(t_philo_data *d)
{
	struct timeval	tv;
	bool			stop;
	
	stop = false;
	if (d->t->philo_count == 1)
	{
		status(d, FORK);
		msleep(d->t->death_time);
		return (true);
	}
	lock_forks(d, &stop);
	stop = stop || status(d , EAT);
	gettimeofday(&tv, NULL);
	msleep(d->t->eat_time);
	pthread_mutex_unlock(&(d->t->forks[d->id - 1]));
	pthread_mutex_unlock(&(d->t->forks[(d->id) % d->t->philo_count]));
	pthread_mutex_lock(&d->lm_lock);
	d->last_meal = get_passed_ms(false);
	pthread_mutex_unlock(&d->lm_lock);
	if (stop)
		return (true);
	return (false);
}

bool	habit_sleep(t_philo_data *d)
{
	if (status(d , SLEEP))
		return (true);
	msleep(d->t->sleep_time);
	return (false);
}

bool	habit_think(t_philo_data *d)
{
	if (status(d , THINK))
		return (true);
	return (false);
}
