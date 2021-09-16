/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/16 12:14:55 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_rules(int *args, t_global *rules)
{
	rules->nb_philo = args[0];
	rules->tto_die = args[1];
	rules->tto_eat = args[2];
	rules->tto_sleep = args[3];
	rules->must_eat_x = args[4];
}

int	ft_min(int x, int y)
{
	if (x < y)
		return (x);
	return (y);
}

int	ft_max(int x, int y)
{
	if (x > y)
		return (x);
	return (y);
}

t_philo	*init_philos(t_global rules)
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
		philo[i].tto_die = rules.tto_die;
		philo[i].tto_eat = rules.tto_eat;
		philo[i].tto_sleep = rules.tto_sleep;
		philo[i].alive = true;
		philo[i].fork_first = ft_min(i, (i + 1) % rules.nb_philo);
		philo[i].fork_second = ft_max(i, (i + 1) % rules.nb_philo);
		printf("philo %d demands fork %d first then fork %d\n", philo[i].id, philo[i].fork_first, philo[i].fork_second);
		i++;
	}
	return (philo);
}

int	main(int ac, char **av)
{
	int			args[MIN_NB_ARG];
	t_global	rules;
	t_philo		*philo;

	if (ac < MIN_NB_ARG || ac > MIN_NB_ARG + 1)
		return (EXIT_FAILURE);
	if (!init_args(ac, av, args))
		return (EXIT_FAILURE);
	init_rules(args, &rules);
	philo = init_philos(rules);
	if (!philo)
		return (EXIT_FAILURE);
		//free_exit(philo);
	for (int i = 0; i < MIN_NB_ARG; i++)
		printf("arg[%d] = %d\n", i, args[i]);
	return (EXIT_SUCCESS);
}
