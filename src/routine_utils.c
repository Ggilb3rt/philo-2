/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:11:01 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/24 17:08:48 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	check_alive(t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_all_alive);
	if (*philo->all_alive == -1)
	{
		pthread_mutex_unlock(philo->mutex_all_alive);
		return (false);
	}
	pthread_mutex_unlock(philo->mutex_all_alive);
	return (true);
}

void	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(philo->mutex_all_alive);
	if (*philo->all_alive != -1)
		print_msg(MSG_TAKE_FORK, philo);
	pthread_mutex_unlock(philo->mutex_all_alive);
}

void	drop_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

t_bool	eat(t_philo *philo)
{
	take_fork(philo, &philo->mutex_forks[philo->fork_first]);
	take_fork(philo, &philo->mutex_forks[philo->fork_second]);
	pthread_mutex_lock(philo->mutex_all_alive);
	if (*philo->all_alive != -1)
		print_msg(MSG_EATING, philo);
	else
	{
		pthread_mutex_unlock(philo->mutex_all_alive);
		drop_fork(&philo->mutex_forks[philo->fork_first]);
		drop_fork(&philo->mutex_forks[philo->fork_second]);
		printf("%d try to eat but one died\n", (philo->id) + 1); // print without error some times and with error 1 time
		return (false);
	}
	pthread_mutex_unlock(philo->mutex_all_alive);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_millis();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	ft_usleep(philo->tto_eat, philo);
	drop_fork(&philo->mutex_forks[philo->fork_first]);
	drop_fork(&philo->mutex_forks[philo->fork_second]);
	if (!check_alive(philo))
		return (false);
	return (true);
}
