/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 08:06:14 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/17 08:18:39 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_millis(void)
{
	struct timeval	now;
	time_t			millis;

	gettimeofday(&now, NULL);
	millis = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (millis);
}
