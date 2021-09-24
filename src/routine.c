/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 08:29:19 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/23 17:35:46 by ggilbert         ###   ########.fr       */
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
	/*pthread_mutex_lock(&philo->mutex_forks[philo->fork_first]);
	print_msg(MSG_TAKE_FORK, philo);
	pthread_mutex_lock(&philo->mutex_forks[philo->fork_second]);
	print_msg(MSG_TAKE_FORK, philo);*/
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
		pthread_mutex_lock(philo->mutex_all_alive);
		*philo->all_alive += 1;
		if (*philo->all_alive != -1)
			print_msg(MSG_SLEEPING, philo);
		else
		{
			pthread_mutex_unlock(philo->mutex_all_alive);
			return (NULL);
		}
		pthread_mutex_unlock(philo->mutex_all_alive);
		ft_usleep(philo->tto_sleep, philo);
		pthread_mutex_lock(philo->mutex_all_alive);
		if (*philo->all_alive != -1)
			print_msg(MSG_THINKING, philo);
		else
		{
			pthread_mutex_unlock(philo->mutex_all_alive);
			return (NULL);
		}
		pthread_mutex_unlock(philo->mutex_all_alive);
		nb_meal++;
	}
	return (NULL);
}

void	*monitor(void *arg)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)arg;
	while (1)
	{
		i = -1;
		while (++i < philo->nb_philo)
		{
			pthread_mutex_lock(philo->mutex_all_alive);
			if (*philo->all_alive == philo->nb_philo * philo->nb_meal)
			{
				pthread_mutex_unlock(philo->mutex_all_alive);
				return (NULL);
			}
			pthread_mutex_lock(&philo[i].mutex_last_meal);
			if (get_millis() - philo[i].last_meal > philo->tto_die)
			{
				print_msg(MSG_DIED, &philo[i]);
				*philo->all_alive = -1;
				pthread_mutex_unlock(&philo[i].mutex_last_meal);
				pthread_mutex_unlock(philo->mutex_all_alive);
				printf("bye\n");
				return (NULL);
			}
			pthread_mutex_unlock(&philo[i].mutex_last_meal);
			pthread_mutex_unlock(philo->mutex_all_alive);
		}
		usleep(100);
	}
	return (NULL);
}
