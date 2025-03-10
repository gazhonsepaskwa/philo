/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:10:29 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/20 12:10:29 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include "utils/utils.h"

int	init_forks(t_table *table)
{
	size_t	i;

	i = 0;
	while (i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}

t_table	*init(char **av, bool *e)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	memset(table, 0, sizeof(t_table));
	table->philo_count = ft_atoi(av[1]);
	table->death_time = ft_atoi(av[2]);
	table->eat_time = ft_atoi(av[3]);
	table->sleep_time = ft_atoi(av[4]);
	table->simstop = false;
	table->done = 0;
	table->max_iter = -1;
	if (av[5])
		table->max_iter = ft_atoi(av[5]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->forks
		|| pthread_mutex_init(&table->print, NULL) != 0
		|| pthread_mutex_init(&table->done_lock, NULL) != 0
		|| pthread_mutex_init(&table->sim_s_lock, NULL) != 0)
		*e = true;
	if (!init_forks(table))
		*e = true;
	get_passed_ms(true);
	return (table);
}
