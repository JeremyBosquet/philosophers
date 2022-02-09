/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:40:14 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/02 11:04:25 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_eat(t_philos *philos, int i)
{
	pthread_mutex_lock(&philos->philo[i].mutex);
	pthread_mutex_lock(&philos->philo[i].fork_r);
	print_action(FORK, philos->philo[i].id, philos);
	pthread_mutex_lock(philos->philo[i].fork_l);
	print_action(FORK, philos->philo[i].id, philos);
	philos->philo[i].last_eat = get_time();
	print_action(EAT, philos->philo[i].id, philos);
	if (philos->philo[i].nb_eat < philos->must_eat)
		philos->philo[i].nb_eat++;
	smart_sleep(philos->time_eat);
	pthread_mutex_unlock(philos->philo[i].fork_l);
	pthread_mutex_unlock(&philos->philo[i].fork_r);
	pthread_mutex_unlock(&philos->philo[i].mutex);
}

int	check_death(t_philos *philos)
{
	suseconds_t	time;
	int			i;

	i = 0;
	while (philos->started)
	{
		time = get_time();
		i = 0;
		while (i < philos->nb_philo)
		{
			if (time - philos->philo[i].last_eat > philos->time_die)
			{
				print_action(DIE, philos->philo[i].id, philos);
				philos->started = 0;
				return (1);
			}
			i++;
			check_nb_eat(philos);
		}
	}
	return (0);
}

int	check_nb_eat(t_philos *philos)
{
	int	i;
	int	all_ate;

	all_ate = 0;
	i = 0;
	if (philos->must_eat == -1)
		return (0);
	while (i < philos->nb_philo)
	{
		if (philos->philo[i].nb_eat < philos->must_eat)
			return (0);
		i++;
	}
	philos->all_ate = 1;
	philos->started = 0;
	return (1);
}

void	*philo(void *param)
{
	t_args	*args;
	int		i;

	args = (t_args *)param;
	i = args->i;
	if (args->i + 1 == args->philos->nb_philo)
	{
		args->philos->started = 1;
		args->philos->start_time = get_time();
	}
	while (!args->philos->started)
		i = i + 1 - 1;
	if (args->philos->philo[i].id % 2)
		usleep(1500);
	while (args->philos->started)
	{
		p_eat(args->philos, i);
		if (args->philos->all_ate)
			break ;
		print_action(SLEEP, args->philos->philo[i].id, args->philos);
		smart_sleep(args->philos->time_sleep);
		if (args->philos->started)
			print_action(THINK, args->philos->philo[i].id, args->philos);
	}
	return (NULL);
}
