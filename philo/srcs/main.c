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

void	destroy(t_table *table)
{
	size_t	i;

	pthread_mutex_destroy(&table->sim_s_lock);
	pthread_mutex_destroy(&table->done_lock);
	pthread_mutex_destroy(&table->print);
	i = -1;
	while (++i < table->philo_count)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos_d[i]->lm_lock);
		free(table->philos_d[i]);
	}
	free(table->philos);
	free(table->forks);
	free(table->philos_d);
	free(table);
}

int	main(int ac, char **av)
{
	t_table			*table;
	unsigned int	pdead;

	if (check_ko(ac, av))
		return (1);
	table = init(av);
	if (!table)
		return (err("Table init failed"));
	if (!create_philos(table))
		return (err("Philo init failed"));
	pdead = wait_end(table);
	if ((int)pdead != -1)
		printf("%lld %d %s\n", get_passed_ms(false), pdead, DIED);
	if (!join_philos(table))
		return (err("Philo join failed"));
	destroy(table);
	return (0);
}
