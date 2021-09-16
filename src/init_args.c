/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 18:25:25 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/16 11:23:11 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

int	ft_pos_atoi(char *s)
{
	long	res;

	res = 0;
	while ((*s >= 9 && *s <= 13) || *s == ' ')
		s++;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			return (-1);
		s++;
	}
	while (ft_isdigit(*s) && *s)
	{
		res = res * 10 + ((char)*s - '0');
		s++;
	}
	if (res > MAX_INT)
		res = MAX_INT;
	return ((int)res);
}

t_bool	all_digits(char *av)
{
	int	k;

	k = 0;
	while (av[k])
	{
		if (!ft_isdigit(av[k]))
			if (!(k == 0 && (av[k] == '-' || av[k] == '+')))
				return (false);
		k++;
	}
	return (true);
}

t_bool	init_args(int ac, char **av, int *args)
{
	int	i;

	i = 1;
	args[MIN_NB_ARG - 1] = -1;
	while (i < ac)
	{
		if (!all_digits(av[i]))
			return (false);
		args[i - 1] = ft_pos_atoi(av[i]);
		if (args[i - 1] == -1)
			return (false);
		i++;
	}
	if (args[0] == 0)
		return (false);
	return (true);
}
