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

void	ft_free(void *var)
{
	if (var)
		free(var);
}

void	free_table(t_table *table)
{
	ft_free(table->philos);
	ft_free(table->forks);
	ft_free(table->philos_d);
	free(table);
}

void	destroy_locks(t_table *table)
{
	pthread_mutex_destroy(&table->sim_s_lock);
	pthread_mutex_destroy(&table->done_lock);
	pthread_mutex_destroy(&table->print);
}

void	destroy(t_table *table, int *e)
{
	size_t	i;

	if (!table)
		return ;
	if (table->philos && table->philos_d)
		join_philos(table);
	destroy_locks(table);
	i = -1;
	while (table->philos && table->philos_d && ++i < table->philo_count)
	{
		if (table->philos_d[i])
			pthread_mutex_destroy(&table->philos_d[i]->lm_lock);
		else
			break ;
		ft_free(table->philos_d[i]);
	}
	i = -1;
	if (*e > 0)
		while (table->forks && ++i < table->philo_count && (int)i < *e)
			pthread_mutex_destroy(&table->forks[i]);
	else
		while (table->forks && ++i < table->philo_count)
			pthread_mutex_destroy(&table->forks[i]);
	free_table(table);
}

int	main(int ac, char **av)
{
	t_table			*table;
	unsigned int	pdead;
	int				e;

	e = 0;
	if (check_ko(ac, av))
		return (1);
	table = init(av, &e);
	if (e != 0 || !table)
		return (destroy(table, &e), err("Table init failed"));
	if (!create_philos(table))
		return (destroy(table, &e), err("A thread creation failed"));
	pdead = wait_end(table);
	(void)pdead;
	if ((int)pdead != -1)
		printf("%lld %d %s\n", get_passed_ms(false), pdead, DIED);
	destroy(table, &e);
	return (0);
}
