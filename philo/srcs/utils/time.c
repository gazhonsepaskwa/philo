/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalebrun <nalebrun@student.s19.be>        +#+  +:+       +#+         */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:06:38 by nalebrun          #+#    #+#             */
/*   Updated: 2025/02/25 13:06:38 by nalebrun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

long long	get_passed_ms(bool first_it)
{
	struct timeval			tv;
	static long long		og_ts;

	gettimeofday(&tv, NULL);
	if (first_it)
	{
		og_ts = ((long long)(tv.tv_sec) *1000) + (tv.tv_usec / 1000);
		first_it = false;
	}
	return (((long long)(tv.tv_sec) *1000) + (tv.tv_usec / 1000) - og_ts);
}
