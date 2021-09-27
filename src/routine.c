/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 08:29:19 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/27 16:41:11 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
/*
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
}*/

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
		*philo->all_alive += 1; // probleme, je +1 avant de regarder si -1 ...
		if (*philo->all_alive == -1)
			break ;
		print_msg(MSG_SLEEPING, philo);
		pthread_mutex_unlock(philo->mutex_all_alive);
		ft_usleep(philo->tto_sleep, philo);
		pthread_mutex_lock(philo->mutex_all_alive);
		if (*philo->all_alive != -1)
			print_msg(MSG_THINKING, philo);
		else
			break ;
		pthread_mutex_unlock(philo->mutex_all_alive);
		nb_meal++;
	}
	pthread_mutex_unlock(philo->mutex_all_alive);
	return (NULL);
}

// error de mutex thread uniquement quand die
// trouve, le thread principal free les mutex
// avant que les detachs ne soient finis
void	*monitor(void *arg)
{
	t_philo	*philo;
	int		total_meal;
	int		i;

	philo = (t_philo *)arg;
	total_meal = philo->nb_philo * philo->nb_meal;
	while (1)
	{
		i = -1;
		while (++i < philo->nb_philo)
		{
			pthread_mutex_lock(philo->mutex_all_alive);
			if (*philo->all_alive == total_meal)
			{
				pthread_mutex_unlock(philo->mutex_all_alive);
				printf("1 out from nb meal\n");
				return (NULL);
			}
			pthread_mutex_lock(&philo[i].mutex_last_meal);
			if (get_millis() - philo[i].last_meal > philo->tto_die)
			{
				print_msg(MSG_DIED, &philo[i]);
				*philo->all_alive = -1;
				pthread_mutex_unlock(&philo[i].mutex_last_meal);
				pthread_mutex_unlock(philo->mutex_all_alive);
				printf("2 out from die\n");
				return (NULL);
			}
			pthread_mutex_unlock(&philo[i].mutex_last_meal);
			pthread_mutex_unlock(philo->mutex_all_alive);
		}
		ft_usleep(10, philo);
	}
	return (NULL);
}
