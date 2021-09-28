/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilbert <ggilbert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 17:44:52 by ggilbert          #+#    #+#             */
/*   Updated: 2021/09/28 16:50:24 by ggilbert         ###   ########.fr       */
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
	pthread_t		thread;
	int				fork_first;
	int				fork_second;
	pthread_mutex_t	*mutex_forks;
	long int		last_meal;
	pthread_mutex_t	mutex_last_meal;
	t_global		*rules;
	long int		nb_meal;
	time_t			time_start;
	int				*eat_x_times;
	pthread_mutex_t	*mutex_eat_x_times;
	int				*all_alive;
	pthread_mutex_t	*mutex_all_alive;
	pthread_mutex_t	*mutex_talk;
}	t_philo;

typedef struct s_monitor
{
	int				eat_x_times;
	pthread_mutex_t	mutex_eat_x_times;
	int				*all_alive;
	pthread_mutex_t	*mutex_all_alive;
	pthread_mutex_t	*mutex_talk;
}	t_monitor;

int				ft_min(int x, int y);
int				ft_max(int x, int y);
void			init_rules(int *args, t_global *rules);
time_t			get_millis(void);
void			ft_usleep(int time, t_philo *philo);
t_bool			print_msg(char *msg, t_philo *philo);

t_bool			init_args(int ac, char **av, t_global *rules);
t_philo			*init_philos(t_global *r, pthread_mutex_t *f, int *a, int *e);
pthread_mutex_t	*init_forks(t_global *rules);

void			start(t_philo *philo);
void			*life(void *arg);
void			*monitor(void *arg);
t_bool			check_alive(t_philo *philo);
t_bool			eat(t_philo *philo);
t_bool			starve(t_philo *philo, int i);

int				ft_free_forks(pthread_mutex_t *forks, t_global *rules);
void			ft_free_philos(t_philo *philo);

#endif
