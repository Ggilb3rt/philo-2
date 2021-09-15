/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/15 18:43:59 by ggilbert         ###   ########.fr       */
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
	rules->all_good = true;
}

int	main(int ac, char **av)
{
	int			args[MIN_NB_ARG];
	t_global	rules;

	if (ac < MIN_NB_ARG || ac > MIN_NB_ARG + 1)
		return (EXIT_FAILURE);
	if (!init_args(ac, av, args))
		return (EXIT_FAILURE);
	init_rules(args, &rules);
	for (int i = 0; i < MIN_NB_ARG; i++)
		printf("arg[%d] = %d\n", i, args[i]);
	return (EXIT_SUCCESS);
}
