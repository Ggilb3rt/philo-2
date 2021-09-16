/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/16 12:26:38 by ggilbert         ###   ########.fr       */
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

# define MAX_INT 2147483647
# define MIN_NB_ARG 5
# define MSG_TAKE_FORK "has taken fork"
# define MSG_EATING "is eating"
# define MSG_SLEEPING "is sleeping"
# define MSG_THINKING "is thinking"

typedef enum e_bool
{
	false = 0,
	true = 1
}	t_bool;

typedef struct s_global
{
	int				nb_philo;
	long int		tto_die;
	long int		tto_eat;
	long int		tto_sleep;
	long int		must_eat_x;
}	t_global;

typedef struct s_philo
{
	int				id;
	t_bool			alive;
	int				fork_first;
	int				fork_second;
	pthread_mutex_t	mutex_first_fork;
	pthread_mutex_t	mutex_second_fork;
	pthread_mutex_t	mutex_check_alive;
	pthread_t		thread;
	long int		last_meal;
	long int		nb_meal;
	long int		tto_die;
	long int		tto_eat;
	long int		tto_sleep;
}	t_philo;

t_bool	init_args(int ac, char **av, int *args);

#endif
