/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:07:14 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/25 13:07:14 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <unistd.h>
# include <stdbool.h>

int			is_extended_digit(char *str);
int			check_ko(int ac, char **av);
long		ft_atoi(const char *str);
long long	get_passed_ms(bool first_it);
void		msleep(int ms);

#endif
