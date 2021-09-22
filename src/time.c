/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 08:06:14 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/22 13:35:50 by ggilbert         ###   ########.fr       */
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

// Seg fault when all_alive used
void	ft_usleep(int time, t_philo *philo)
{
	time_t	stop;
	time_t	now;

	now = get_millis();
	stop = now + time;
	while (get_millis() < stop)
	{
		pthread_mutex_lock(philo->mutex_all_alive);
		if (*philo->all_alive == -1)
			return ;
		pthread_mutex_unlock(philo->mutex_all_alive);
		usleep(100);
	}
}