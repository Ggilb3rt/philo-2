/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:36:27 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/28 16:51:15 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
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
	//pthread_t	monitor_thread;
	int			starter;

	starter = 0;
	now = get_millis();
	start_half_philo(philo, starter, now);
	ft_usleep(10, philo);
	start_half_philo(philo, ++starter, now);
	monitor(philo);
	//pthread_create(&monitor_thread, NULL, monitor, philo);
	//pthread_join(monitor_thread, NULL);
}
*/
void	*life_alone(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)(arg);
	pthread_mutex_lock(&philo->mutex_forks[philo->fork_first]);
	print_msg(MSG_TAKE_FORK, philo);
	pthread_mutex_unlock(&philo->mutex_forks[philo->fork_first]);
	return (NULL);
}

t_bool	solo_philo(t_philo *philo, time_t now)
{
	int	err;

	philo[0].time_start = now;
	philo[0].last_meal = get_millis();
	err = pthread_create(&(philo[0].thread), NULL, life_alone, &philo[0]);
	if (err != 0)
		return (false);
	return (true);
}

t_bool	create_th_philo(t_philo *philo, int start, time_t now)
{
	int	err;

	if (philo->rules->nb_philo == 1)
	{
		if (solo_philo(philo, now))
			return (true);
		else
			return (false);
	}
	else
	{
		while (start < philo->rules->nb_philo)
		{
			philo[start].time_start = now;
			philo[start].last_meal = get_millis();
			err = pthread_create(&(philo[start].thread),
					NULL, life, &philo[start]);
			if (err != 0)
				return (false);
			start += 2;
		}
	}
	return (true);
}

void	join_all(t_philo *philo)
{
	int	start;

	start = 0;
	while (start < philo->rules->nb_philo)
	{
		pthread_join(philo[start].thread, NULL);
		start++;
	}
}

void	start(t_philo *philo)
{
	time_t		now;
	int			starter;

	starter = 0;
	now = get_millis();
	if (!create_th_philo(philo, starter, now))
		return ;
	if (philo->rules->nb_philo != 1)
	{
		ft_usleep(10, philo);
		if (!create_th_philo(philo, ++starter, now))
			return ;
	}
	monitor(philo);
	join_all(philo);
}
