/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/15 17:54:51 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define MIN_NB_ARG 5

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_global
{
	unsigned int	nb_philo;
	long int		tto_die;
	long int		tto_eat;
	long int		tto_sleep;
	long int		must_eat;
	t_bool			all_good;
}	t_global;

typedef struct s_philo
{
	unsigned int	id;
	t_bool			alive;
	pthread_mutex_t	left_hand;
	pthread_mutex_t	right_hand;
}	t_philo;

#endif
