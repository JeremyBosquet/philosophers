/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:40:14 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/18 15:30:20 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	p_eat(t_philos *philos, int i)
{
	//pthread_mutex_lock(&philos->philo[i].mutex);
	pthread_mutex_lock(philos->philo[i].fork_l);
	print_action(FORK, philos->philo[i].id, philos);
	pthread_mutex_lock(&philos->philo[i].fork_r);
	print_action(FORK, philos->philo[i].id, philos);
	philos->philo[i].last_eat = get_time();
	print_action(EAT, philos->philo[i].id, philos);
	philos->philo[i].nb_eat++;
	usleep(philos->time_eat * 1000);
	pthread_mutex_unlock(philos->philo[i].fork_l);
	pthread_mutex_unlock(&philos->philo[i].fork_r);
	//pthread_mutex_unlock(&philos->philo[i].mutex);
}

int	check_death(t_philos *philos)
{
	int	i;

	i = 0;
	while (philos->started && i < philos->nb_philo)
	{
		pthread_mutex_lock(&philos->philo[i].mutex);
		if (philos->philo[i].last_eat != 0
			&& time_diff(philos->philo[i].last_eat,
				get_time()) > philos->time_die)
		{
			print_action(DIE, philos->philo[i].id, philos);
			philos->died = 1;
			return (1);
		}
		pthread_mutex_unlock(&philos->philo[i].mutex);
		i++;
	}
	return (0);
}

int	check_nb_eat(t_philos *philos)
{
	int	i;
	int	all_ate;

	all_ate = 0;
	i = 0;
	if (philos->started && philos->must_eat != -1)
	{
		while (i < philos->nb_philo)
			if (philos->philo[i++].nb_eat >= philos->must_eat)
				all_ate++;
		if (all_ate == philos->nb_philo)
		{
			philos->all_ate = 1;
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

void	*philo(void *param)
{
	t_args	*args;
	int		i;

	args = (t_args *)param;
	i = args->i;
	if (args->i + 1 == args->philos->nb_philo)
		args->philos->started = 1;
	if (args->philos->philo[i].id % 2)
		usleep(1500);
	while (!check_death(args->philos))
	{
		if (!args->philos->all_ate)
		{
			p_eat(args->philos, i);
			if (args->philos->must_eat != -1 && args->philos->all_ate)
				return (NULL);
			print_action(SLEEP, args->philos->philo[i].id, args->philos);
			usleep(args->philos->time_sleep * 1000);
			print_action(THINK, args->philos->philo[i].id, args->philos);
		}
		else
			return (NULL);
	}
	return (NULL);
}
