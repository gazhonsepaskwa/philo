/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:14:25 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/20 14:14:25 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../philo.h"
#include "../utils/utils.h"

void *philo_core(void *raw_data)
{
	t_philo_data	*data;
	size_t			i;
	bool			error;

	i = 0;
	error = false;
	data = (t_philo_data *)raw_data;
	if (data->id % 2 != 0)
		msleep(data->t->eat_time / 2);
	while (i < data->t->max_iter)
	{
		error = error || habit_eat(data);
		error = error || habit_sleep(data);
		i++;
		if (i == data->t->max_iter)
			break;
		error = error || habit_think(data);
		if (error)
			break;
	}
	pthread_mutex_lock(&data->t->done_lock);
	data->t->done += 1;
	pthread_mutex_unlock(&data->t->done_lock);
	return (NULL);
}

int	create_philos(t_table *table)
{
	size_t			i;

	i = 0;
	table->philos = malloc(sizeof(pthread_t) * table->philo_count);
	table->philos_d = malloc(sizeof(t_philo_data *) * table->philo_count);
	while (i < table->philo_count)
	{
		table->philos_d[i] = malloc(sizeof(t_philo_data));
		table->philos_d[i]->t = table;
		table->philos_d[i]->id = i + 1;
		table->philos_d[i]->last_meal = 0;
		pthread_mutex_init(&table->philos_d[i]->lm_lock, NULL);
		if (pthread_create(&table->philos[i], NULL, philo_core,
					 (void *)table->philos_d[i]) != 0)
			return (0);
		i++;
	}
	return (1);
}


int join_philos(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_join(table->philos[i], NULL))
			return (0);
		i++;
	}
	return (1);
}
