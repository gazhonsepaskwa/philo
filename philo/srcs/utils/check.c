/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:06:00 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/25 13:06:00 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	check_ko(int ac, char **av)
{
	int	i;

	if (ac < 5 || ac > 6)
		return (write(2, "Usage: ./philo philo_count die_time eat_time \
sleep_time [eat_occurencies]\n", 75));
	if (ft_atoi(av[1]) == 0)
		return (write(2, "Arg error\n", 10));
	i = 0;
	while (++i < ac)
	{
		if (!is_extended_digit(av[i])
			|| ft_atoi(av[i]) == 235087234809897094
			|| ft_atoi(av[i]) == 0)
			return (write(2, "Arg error\n", 10));
	}
	return (0);
}
