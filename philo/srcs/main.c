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

int8_t	err(char *msg)
{
	printf("\033[31m%s\033[0m\n", msg);
	return (1);
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
	if (!join_philos(table))
		return (err("Philo init failed"));
	if (CUTE)
		printf("┗━━━━━━━━━━━━━━━━━━━━━━┻━━━━━━┻━━━━━━━━━━━━━━━━━━━┛\n");
	return (0);
}
