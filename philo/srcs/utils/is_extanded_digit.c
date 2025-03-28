/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_extanded_digit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:05:17 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/25 13:05:17 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	is_digit(int n)
{
	if (n < 48 || n > 57)
		return (0);
	else
		return (1);
}

int	is_extended_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			i++;
		if (!is_digit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
