/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/24 17:43:02 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	print_msg(char *msg, t_philo *philo)
{
	pthread_mutex_lock(philo->mutex_talk);
	printf("%6ld %d %s\n", get_millis() - philo->time_start, philo->id + 1, msg);
	pthread_mutex_unlock(philo->mutex_talk);
}

int	main(int ac, char **av)
{
	int				args[MIN_NB_ARG];
	t_global		rules;
	t_philo			*philo;
	pthread_mutex_t	*forks;
	int				*all_alive;

	if (ac < MIN_NB_ARG || ac > MIN_NB_ARG + 1)
		return (EXIT_FAILURE);
	if (!init_args(ac, av, args))
		return (EXIT_FAILURE);
	init_rules(args, &rules);
	forks = init_forks(&rules);
	if (!forks)
		return (EXIT_FAILURE);
	all_alive = malloc(sizeof(int));
	if (!all_alive)
		return (EXIT_FAILURE);
	*all_alive = 0;
	philo = init_philos(rules, forks, all_alive);
	if (!philo)
		return (ft_free_forks(forks, &rules));
	start(philo);
	printf("before free\n");
	ft_free_forks(forks, &rules);
	ft_free_philos(philo);
	free(all_alive);
	printf("end");
	return (EXIT_SUCCESS);
}
