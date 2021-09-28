/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:49:41 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/28 17:03:12 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free_forks(pthread_mutex_t *forks, t_global *rules)
{
	int	i;

	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	free(forks);
	return (0);
}

void	ft_free_philos(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].mutex_last_meal);
		i++;
	}
	pthread_mutex_destroy(philo->mutex_all_alive);
	pthread_mutex_destroy(philo->mutex_talk);
	pthread_mutex_destroy(philo->mutex_eat_x_times);
	free(philo->mutex_all_alive);
	free(philo->mutex_talk);
	free(philo->mutex_eat_x_times);
	free(philo);
}
