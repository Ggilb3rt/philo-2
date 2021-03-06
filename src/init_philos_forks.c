/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 17:33:26 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/28 16:52:33 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//philo[i].fork_first = ft_min(i, (i + 1) % rules.nb_philo);
//philo[i].fork_second = ft_max(i, (i + 1) % rules.nb_philo);
//printf("philo %d demands fork %d first then fork %d\n",
//			philo[i].id + 1, philo[i].fork_first + 1, philo[i].fork_second + 1);
t_philo	*init_philo_basics(t_global *rules, pthread_mutex_t *f, int *a, int *e)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * (rules->nb_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		philo[i].id = i;
		philo[i].rules = rules;
		philo[i].eat_x_times = e;
		philo[i].nb_meal = rules->must_eat_x;
		philo[i].all_alive = a;
		philo[i].fork_first = i;
		philo[i].fork_second = i - 1;
		if (i == 0)
			philo[i].fork_second = rules->nb_philo - 1;
		philo[i].mutex_forks = f;
		i++;
	}
	return (philo);
}

t_philo	*init_philos(t_global *rules, pthread_mutex_t *f, int *all_a, int *e)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*mutex[NB_SHARED_VAR_PHILO];

	philo = init_philo_basics(rules, f, all_a, e);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < NB_SHARED_VAR_PHILO)
	{
		mutex[i] = malloc(sizeof(pthread_mutex_t));
		if (!mutex[i])
			return (NULL);
		pthread_mutex_init(mutex[i], NULL);
		i++;
	}
	i = -1;
	while (++i < rules->nb_philo)
	{
		philo[i].mutex_all_alive = mutex[0];
		philo[i].mutex_talk = mutex[1];
		philo[i].mutex_eat_x_times = mutex[2];
		pthread_mutex_init(&philo[i].mutex_last_meal, NULL);
	}
	return (philo);
}

pthread_mutex_t	*init_forks(t_global *rules)
{
	int				i;
	pthread_mutex_t	*forks;

	forks = malloc(sizeof(pthread_mutex_t) * rules->nb_philo);
	if (!forks)
		return (NULL);
	i = 0;
	while (i < rules->nb_philo)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (forks);
}
