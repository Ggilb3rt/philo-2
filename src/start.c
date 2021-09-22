/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:36:27 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/22 17:49:49 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Dois-je attraper une erreur de thread_create ?

si le thread ne se lance pas detach bug ?
*/
void	start_half_philo(t_philo *philo, int start, time_t now, int *all_alive)
{
	int	err;

	err = 0;
	while (start < philo->nb_philo)
	{
		philo[start].last_meal = get_millis();
		philo[start].time_start = now;
		philo[start].all_alive = all_alive;
		err = pthread_create(&(philo[start].thread), NULL, life, &philo[start]);
		//if ()
		pthread_detach(philo[start].thread);
		start += 2;
	}
}

void	start(t_philo *philo)
{
	time_t		now;
	pthread_t	monitor_thread;
	int			i;
	int			starter;
	int			all_alive;

	i = 0;
	starter = 0;
	all_alive = 0;
	now = get_millis();
	printf("START / %ld\n", now);
	start_half_philo(philo, starter, now, &all_alive);
	ft_usleep(10, philo);
	start_half_philo(philo, ++starter, now, &all_alive);
	pthread_create(&monitor_thread, NULL, monitor, philo);
	pthread_join(monitor_thread, NULL);
	printf("END / %ld\n", get_millis());
}
