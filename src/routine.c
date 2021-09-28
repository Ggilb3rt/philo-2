/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 08:29:19 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/28 16:52:54 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*life(void *arg)
{
	t_philo	*philo;
	int		nb_meal;

	nb_meal = 0;
	philo = (t_philo *)(arg);
	while (nb_meal < philo->nb_meal || philo->nb_meal == -1)
	{
		if (!check_alive(philo))
			return (NULL);
		if (eat(philo) == 0)
			return (NULL);
		pthread_mutex_lock(philo->mutex_eat_x_times);
		*philo->eat_x_times += 1;
		pthread_mutex_unlock(philo->mutex_eat_x_times);
		if (!check_alive(philo))
			return (NULL);
		print_msg(MSG_SLEEPING, philo);
		ft_usleep(philo->rules->tto_sleep, philo);
		if (!check_alive(philo))
			return (NULL);
		print_msg(MSG_THINKING, philo);
		nb_meal++;
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		total_meal;
	int		i;

	philo = (t_philo *)arg;
	total_meal = philo->rules->nb_philo * philo->nb_meal;
	while (1)
	{
		i = -1;
		while (++i < philo->rules->nb_philo)
		{
			pthread_mutex_lock(philo->mutex_eat_x_times);
			if (*philo->eat_x_times == total_meal)
			{
				pthread_mutex_unlock(philo->mutex_eat_x_times);
				return (NULL);
			}
			pthread_mutex_unlock(philo->mutex_eat_x_times);
			if (starve(philo, i))
				return (NULL);
		}
		ft_usleep(5, philo);
	}
}
