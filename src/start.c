/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:36:27 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/24 18:04:07 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
Dois-je attraper une erreur de thread_create ?

si le thread ne se lance pas detach bug ?
*/

void	start_half_philo(t_philo *philo, int start, time_t now)
{
	while (start < philo->nb_philo)
	{
		philo[start].last_meal = get_millis();
		philo[start].time_start = now;
		pthread_create(&(philo[start].thread), NULL, life, &philo[start]);
		pthread_detach(philo[start].thread);
		start += 2;
	}
}

void	start(t_philo *philo)
{
	time_t		now;
	pthread_t	monitor_thread;
	int			starter;

	starter = 0;
	now = get_millis();
	start_half_philo(philo, starter, now);
	ft_usleep(10, philo);
	start_half_philo(philo, ++starter, now);
	pthread_create(&monitor_thread, NULL, monitor, philo);
	pthread_join(monitor_thread, NULL);
}
/*

t_bool	create_th_philo(t_philo *philo, int start, time_t now)
{
	int	err;

	while (start < philo->nb_philo)
	{
		philo[start].time_start = now;
		philo[start].last_meal = get_millis();
		err = pthread_create(&(philo[start].thread), NULL, life, &philo[start]);
		//err = 0;
		if (err != 0)
			return (false);
		start += 2;
	}
	return (true);
}

void	join_all(t_philo *philo)
{
	int start;
	int err;

	start = 0;
	err = 0;
	printf("starting join_all\n");
	while (start < philo->nb_philo)
	{
		printf("pouet\n");
		err = pthread_join(philo[start].thread, NULL);
		printf("pouet %d", err);
		start++;
	}
}

void	start(t_philo *philo)
{
	time_t		now;
	pthread_t	monitor_thread;
	int			starter;
	//int			i;

	starter = 0;
	now = get_millis();
	if (!create_th_philo(philo, starter, now))
		return ;
	ft_usleep(10, philo);
	if (!create_th_philo(philo, ++starter, now))
		return ;
	pthread_create(&monitor_thread, NULL, monitor, philo);
	//start_half_philo(philo, starter);
	//ft_usleep(10, philo);
	//start_half_philo(philo, ++starter);
	pthread_join(monitor_thread, NULL);
	printf("between joins\n");
	join_all(philo);
	printf("end of start()\n");
}
*/