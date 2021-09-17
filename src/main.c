/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/17 12:06:38 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_talk);
	printf("%06ld %d %s\n", get_millis() - philo->time_start, philo->id + 1, msg);
	pthread_mutex_unlock(philo->mutex_talk);
}

void	init_rules(int *args, t_global *rules)
{
	rules->nb_philo = args[0];
	rules->tto_die = args[1];
	rules->tto_eat = args[2];
	rules->tto_sleep = args[3];
	rules->must_eat_x = args[4];
}

t_philo	*init_philo_basics(t_global rules, pthread_mutex_t *forks)
{
	int		i;
	t_philo	*philo;

	philo = malloc(sizeof(t_philo) * (rules.nb_philo));
	if (!philo)
		return (NULL);
	i = 0;
	while (i < rules.nb_philo)
	{
		philo[i].id = i;
		philo[i].nb_meal = rules.must_eat_x;
		philo[i].tto_die = rules.tto_die;
		philo[i].tto_eat = rules.tto_eat;
		philo[i].tto_sleep = rules.tto_sleep;
		philo[i].alive = true;
		philo[i].nb_philo = rules.nb_philo;
		philo[i].all_alive = 0;
		philo[i].fork_first = ft_min(i, (i + 1) % rules.nb_philo);
		philo[i].fork_second = ft_max(i, (i + 1) % rules.nb_philo);
		philo[i].mutex_forks = forks;
		printf("philo %d demands fork %d first then fork %d\n",
			philo[i].id + 1, philo[i].fork_first + 1, philo[i].fork_second + 1);
		i++;
	}
	return (philo);
}

t_philo	*init_philos(t_global rules, pthread_mutex_t *forks)
{
	int				i;
	t_philo			*philo;
	pthread_mutex_t	*mutex[NB_SHARED_VAR_PHILO];

	philo = init_philo_basics(rules, forks);
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
	while (++i < rules.nb_philo)
	{
		philo[i].mutex_all_alive = mutex[0];
		philo[i].mutex_alive = mutex[1];
		philo[i].mutex_talk = mutex[2];
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

int	main(int ac, char **av)
{
	int				args[MIN_NB_ARG];
	t_global		rules;
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (ac < MIN_NB_ARG || ac > MIN_NB_ARG + 1)
		return (EXIT_FAILURE);
	if (!init_args(ac, av, args))
		return (EXIT_FAILURE);
	init_rules(args, &rules);
	forks = init_forks(&rules);
	if (!forks)
		return (EXIT_FAILURE);
	philo = init_philos(rules, forks);
	if (!philo)
		return (ft_free_forks(forks, &rules));
	start(philo, &rules);
	return (EXIT_SUCCESS);
}
