/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:47:15 by jbosquet          #+#    #+#             */
/*   Updated: 2022/03/02 09:36:41 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <sys/time.h>
# include <time.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philos
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	long int		time_start;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	mutex_dead;
	pthread_mutex_t	mutex_time_eat;
	pthread_mutex_t	mutex_finish;
	int				nb_p_finish;
	int				stop;
}	t_philos;

typedef struct s_philo
{
	int				id;
	long int		last_eat;
	size_t			nb_eat;
	int				finish;
	pthread_t		thread;
	pthread_t		thread_death;
	pthread_mutex_t	*fork_r;
	pthread_mutex_t	fork_l;
	t_philos		*arg;
}	t_philo;

typedef struct s_args
{
	t_philo		*philo;
	t_philos	arg;
}	t_args;

//Thread

//Init
int			parsing(int argc, char **argv, t_args *philos);
int			init(t_args *philos);
int			launch_threads(t_args *philos);
//Functions
int			ft_error(char *str);
void		ft_putstr_fd(char *str, int fd);
int			ft_strlen(char *str);
int			ft_atoi_simplified(const char *str);
suseconds_t	get_time(void);
void		smart_sleep(long time);
int			check_death(t_philo *philo, int i);
int			check_death2(t_args *philos);
void		print_action(char *action, t_philo *philo);
void		routine(t_philo *ph);

#endif