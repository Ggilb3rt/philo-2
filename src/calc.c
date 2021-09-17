/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:08:38 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/17 07:09:02 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
