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

void	status(t_philo_data *data, char *msg)
{
	pthread_mutex_lock(&data->t->print);
	if (CUTE)
		printf("┃ %-21lld┃ %-4d ┃ %-18s┃\n", get_passed_ms(), data->id, msg);
	else
		printf("%lld %d %s\n", get_passed_ms(), data->id, msg);
	pthread_mutex_unlock(&data->t->print);
}

void	habit_eat(t_philo_data *d)
{
	status(d , FORK);
	if (d->id % 2)
		pthread_mutex_lock(&(d->t->forks[d->id - 1]));
	else
		pthread_mutex_lock(&(d->t->forks[(d->id) % d->t->philo_count]));
	status(d , FORK);
	if (d->id % 2)
		pthread_mutex_lock(&(d->t->forks[(d->id) % d->t->philo_count]));
	else
		pthread_mutex_lock(&(d->t->forks[d->id - 1]));
	status(d , EAT);
	// last_meal = 
	msleep(d->t->eat_time);
	pthread_mutex_unlock(&(d->t->forks[d->id - 1]));
	pthread_mutex_unlock(&(d->t->forks[(d->id) % d->t->philo_count]));
}

void	habit_sleep(t_philo_data *d)
{
	status(d , SLEEP);
	msleep(d->t->sleep_time);
}

void	habit_think(t_philo_data *d)
{
	status(d , THINK);
}
