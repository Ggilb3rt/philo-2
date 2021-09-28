/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:11:01 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/28 16:41:28 by ggilbert         ###   ########.fr       */
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
	print_msg(MSG_TAKE_FORK, philo);
}

void	drop_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

t_bool	eat(t_philo *philo)
{
	take_fork(philo, &philo->mutex_forks[philo->fork_first]);
	take_fork(philo, &philo->mutex_forks[philo->fork_second]);
	if (!print_msg(MSG_EATING, philo))
	{
		drop_fork(&philo->mutex_forks[philo->fork_first]);
		drop_fork(&philo->mutex_forks[philo->fork_second]);
		return (false);
	}
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_millis();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	ft_usleep(philo->rules->tto_eat, philo);
	drop_fork(&philo->mutex_forks[philo->fork_first]);
	drop_fork(&philo->mutex_forks[philo->fork_second]);
	if (!check_alive(philo))
		return (false);
	return (true);
}

t_bool	starve(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo[i].mutex_last_meal);
	if (get_millis() - philo[i].last_meal > philo->rules->tto_die)
	{
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
		print_msg(MSG_DIED, &philo[i]);
		pthread_mutex_lock(philo->mutex_all_alive);
		*philo->all_alive = -1;
		pthread_mutex_unlock(philo->mutex_all_alive);
		return (true);
	}
	pthread_mutex_unlock(&philo[i].mutex_last_meal);
	return (false);
}
