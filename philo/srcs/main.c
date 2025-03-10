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
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

int8_t	err(char *msg)
{
	printf("\033[31m%s\033[0m\n", msg);
	return (1);
}

void	ft_free(void *var)
{
	if (var)
		free(var);
}

void	destroy(t_table *table)
{
	size_t	i;

	join_philos(table);
	pthread_mutex_destroy(&table->sim_s_lock);
	pthread_mutex_destroy(&table->done_lock);
	pthread_mutex_destroy(&table->print);
	i = -1;
	while (table->philos_d && ++i < table->philo_count)
	{
		pthread_mutex_destroy(&table->philos_d[i]->lm_lock);
		ft_free(table->philos_d[i]);
	}
	i = -1;
	while (table->forks && ++i < table->philo_count)
		pthread_mutex_destroy(&table->forks[i]);
	ft_free(table->philos);
	ft_free(table->forks);
	ft_free(table->philos_d);
	free(table);
}

int	main(int ac, char **av)
{
	t_table			*table;
	unsigned int	pdead;
	bool			e;

	e = false;
	if (check_ko(ac, av))
		return (1);
	table = init(av, &e);
	if (e)
		return (destroy(table), err("Table init failed; exiting"));
	if (!create_philos(table))
		return (destroy(table), err("A thread creation failed; exiting"));
	pdead = wait_end(table);
	(void)pdead;
	if ((int)pdead != -1)
		printf("%lld %d %s\n", get_passed_ms(false), pdead, DIED);
	destroy(table);
	return (0);
}
