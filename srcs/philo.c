/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:40:14 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/17 15:24:43 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_eat(t_philos *philos, int i)
{
	pthread_mutex_lock(philos->philo[i].fork_l);
	print_action(FORK, philos->philo[i].id, philos);
	pthread_mutex_lock(&philos->philo[i].fork_r);
	print_action(FORK, philos->philo[i].id, philos);
	philos->philo[i].last_eat = get_time();
	usleep(philos->time_eat);
	print_action(EAT, philos->philo[i].id, philos);
	pthread_mutex_unlock(philos->philo[i].fork_l);
	pthread_mutex_unlock(&philos->philo[i].fork_r);
}

int	check_death(t_philos *philos)
{
	int	i;

	i = 0;
	while (i < philos->nb_philo)
	{
		pthread_mutex_lock(&philos->philo[i].mutex);
		if (time_diff(get_time(), philos->philo[i].last_eat) > philos->time_die)
		{
			print_action(DIE, philos->philo[i].id, philos);
			return (1);
		}
		if (philos->philo[i].dead)
		{		
			print_action(DIE, philos->philo[i].id, philos);
			return (1);
		}
		pthread_mutex_unlock(&philos->philo[i].mutex);
		i++;
	}
	return (0);
}

void	*philo(void *param)
{
	t_args	*args;
	int		i;

	args = (t_args *)param;
	i = args->i;
	if (args->philos->philo[i].id % 2)
		usleep(10);
	while (1)
	{
		if (check_death(args->philos))
			break ;
		p_eat(args->philos, i);
		print_action(SLEEP, args->philos->philo[i].id, args->philos);
		usleep(args->philos->time_sleep);
		print_action(THINK, args->philos->philo[i].id, args->philos);
	}
	return (NULL);
}
