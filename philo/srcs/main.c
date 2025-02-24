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
	destroy(table);
	return (0);
}
