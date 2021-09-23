/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/23 14:36:49 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <string.h>

void	print_msg(char *msg, t_philo *philo)
{
	int die;

	die = strcmp(msg, MSG_DIED);
	printf("diiiiie %d\n", die);
	//le probleme est que si il meurt il ne peut pas le print ==> loop
	pthread_mutex_lock(philo->mutex_all_alive);
	if (*philo->all_alive == -1 && !die)
		return ;
	pthread_mutex_lock(philo->mutex_talk);
	printf("%6ld %d %s\n", get_millis() - philo->time_start, philo->id + 1, msg);
	pthread_mutex_unlock(philo->mutex_talk);
	pthread_mutex_unlock(philo->mutex_all_alive);
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
	start(philo);
	ft_free_forks(forks, &rules);
	ft_free_philos(philo);
	return (EXIT_SUCCESS);
}
