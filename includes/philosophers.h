/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:31:32 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/28 13:14:15 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "libft.h"
# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>

# define FORK 0
# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_philo
{
	int				id;
	int				nb_eat;
	int				dead;
	pthread_mutex_t	fork_r;
	pthread_mutex_t	*fork_l;
	suseconds_t		last_eat;
	pthread_mutex_t	mutex;
	pthread_t		thread;
}	t_philo;

typedef struct s_philos
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				started;
	int				died;
	int				all_ate;
	void			*info;
	pthread_mutex_t	write_mutex;
	suseconds_t		start_time;
	suseconds_t		last_action_time;
	t_philo			*philo;
	t_fork			*fork;
}	t_philos;

typedef struct s_args
{
	t_philos		*philos;
	int				i;
}	t_args;

//Thread
void		threads_start(t_philos *philos);
void		*philo(void *args);

//Init
void		init(char **argv, int argc, t_philos *philos);

//Functions
int			ft_atoi_simplified(const char *str);
suseconds_t	get_time(void);
suseconds_t	time_diff(suseconds_t time1, suseconds_t time2);
void		print_action(int action, int philo_id, t_philos *philos);
int			check_death(t_philos *philos);
int			check_nb_eat(t_philos *philos);
void		free_philo(t_philos *philos);
void		smart_sleep(long time);

#endif