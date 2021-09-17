/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/17 12:05:20 by ggilbert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define MAX_INT 2147483647
# define MIN_NB_ARG 5
# define MSG_TAKE_FORK "has taken a fork"
# define MSG_EATING "is eating"
# define MSG_SLEEPING "is sleeping"
# define MSG_THINKING "is thinking"
# define MSG_DIED "died"
# define NB_SHARED_VAR_PHILO 3

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
	pthread_mutex_t	*mutex_alive;
	pthread_t		thread;
	int				fork_first;
	int				fork_second;
	pthread_mutex_t	*mutex_forks;
	long int		last_meal;
	pthread_mutex_t	mutex_last_meal;
	long int		nb_meal;
	long int		tto_die;
	long int		tto_eat;
	long int		tto_sleep;
	time_t			time_start;
	int				nb_philo;
	int				*all_alive;
	pthread_mutex_t	*mutex_all_alive;
	pthread_mutex_t	*mutex_talk;
}	t_philo;

int		ft_min(int x, int y);
int		ft_max(int x, int y);
time_t	get_millis(void);
void	print_msg(char *msg, t_philo *philo);

t_bool	init_args(int ac, char **av, int *args);
void	start(t_philo *philo, t_global *rules);
void	*life(void *arg);

int		ft_free_forks(pthread_mutex_t *forks, t_global *rules);

#endif
