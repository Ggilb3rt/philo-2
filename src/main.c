/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/28 16:38:44 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_all_alive);
	if (*philo->all_alive != -1)
	{
		pthread_mutex_lock(philo->mutex_talk);
		printf("%6ld %d %s\n", get_millis() - philo->time_start,
			philo->id + 1, msg);
		pthread_mutex_unlock(philo->mutex_talk);
		pthread_mutex_unlock(philo->mutex_all_alive);
		return (true);
	}
	pthread_mutex_unlock(philo->mutex_all_alive);
	return (false);
}

int	main(int ac, char **av)
{
	t_global		rules;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				all_alive;
	int				eat_x_times;

	if (ac < MIN_NB_ARG || ac > MIN_NB_ARG + 1)
		return (EXIT_FAILURE);
	if (!init_args(ac, av, &rules))
		return (EXIT_FAILURE);
	forks = init_forks(&rules);
	if (!forks)
		return (EXIT_FAILURE);
	all_alive = 0;
	eat_x_times = 0;
	philo = init_philos(&rules, forks, &all_alive, &eat_x_times);
	if (!philo)
		return (ft_free_forks(forks, &rules));
	start(philo);
	ft_free_forks(forks, &rules);
	ft_free_philos(philo);
	return (EXIT_SUCCESS);
}
