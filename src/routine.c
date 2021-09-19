/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 08:29:19 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/19 10:38:10 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_forks[philo->fork_first]);
	print_msg(MSG_TAKE_FORK, philo);
	pthread_mutex_lock(&philo->mutex_forks[philo->fork_second]);
	print_msg(MSG_TAKE_FORK, philo);
	print_msg(MSG_EATING, philo);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_millis();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	usleep(philo->tto_eat);
	//pthread_mutex_lock(philo->mutex_all_alive);
	//if (*philo->all_alive != -1)
	//	*(philo->all_alive) += 1;
	//else
	//	return (0);
	pthread_mutex_unlock(philo->mutex_all_alive);
	pthread_mutex_unlock(&philo->mutex_forks[philo->fork_first]);
	pthread_mutex_unlock(&philo->mutex_forks[philo->fork_second]);
	return (1);
}

void	*life(void *arg)
{
	t_philo	*philo;
	int		nb_meal;

	nb_meal = 0;
	philo = (t_philo *)(arg);
	while (nb_meal < philo->nb_meal || philo->nb_meal == -1)
	{
		pthread_mutex_lock(philo->mutex_all_alive);
		//if (*philo->all_alive == -1)
		//	return (NULL);
		pthread_mutex_unlock(philo->mutex_all_alive);
		eat(philo);
		//check if everybody is ok
		print_msg(MSG_SLEEPING, philo);
		usleep(philo->tto_sleep);
		//check if everybody is ok
		print_msg(MSG_THINKING, philo);
		//printf("philo %d meal %d\n", philo->id + 1, nb_meal);
		if (philo->nb_meal == -1)
			return (NULL);
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
				return (NULL);
			pthread_mutex_lock(&philo[i].mutex_last_meal);
			if (get_millis() - philo[i].last_meal > philo->tto_die)
			{
				print_msg(MSG_DIED, &philo[i]);
				//*philo->all_alive = -1;
				return (NULL);
			}
			pthread_mutex_unlock(&philo[i].mutex_last_meal);
			pthread_mutex_unlock(philo->mutex_all_alive);
		}
		usleep(100);
	}
	return (NULL);
}

// need to check thread_create error (maybe create thread in init and join them here)
void	start_half_philo(t_philo *philo, t_global *r, int start, time_t now)
{
	while (start < r->nb_philo)
	{
		philo[start].last_meal = get_millis();
		philo[start].time_start = now;
		pthread_create(&(philo[start].thread), NULL, life, &philo[start]);
		pthread_detach(philo[start].thread);
		start += 2;
	}
}

void	start(t_philo *philo, t_global *rules)
{
	time_t		now;
	pthread_t	monitor_thread;
	int			i;
	int			starter;

	i = 0;
	starter = 0;
	now = get_millis();
	printf("START / %ld\n", now);
	start_half_philo(philo, rules, starter, now);
	usleep(10);
	start_half_philo(philo, rules, ++starter, now);
	pthread_create(&monitor_thread, NULL, monitor, philo);
	pthread_join(monitor_thread, NULL);
}
