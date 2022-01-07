/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:31:32 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/07 14:58:58 by jbosquet         ###   ########.fr       */
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
	int			id;
	int			nb_eat;
	int			nb_fork;
	pthread_t	thread;
}	t_philo;

typedef struct s_philos
{
	int				nb_philo;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				must_eat;
	int				started;
	pthread_mutex_t	write_mutex;
	suseconds_t		start_time;
	suseconds_t		last_action_time;
	t_philo			*philo;
	t_fork			*fork;
}	t_philos;

//Init
void		init(char **argv, int argc, t_philos *philos);

//Functions
suseconds_t	get_time(void);
suseconds_t	time_diff(suseconds_t time1, suseconds_t time2);
void		print_action(int action, int philo_id, t_philos *philos);

#endif