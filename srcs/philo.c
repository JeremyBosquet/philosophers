/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:40:14 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/28 11:58:18 by jbosquet         ###   ########.fr       */
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
	philos->philo[i].nb_eat++;
	smart_sleep(philos->time_eat);
	pthread_mutex_unlock(philos->philo[i].fork_l);
	pthread_mutex_unlock(&philos->philo[i].fork_r);
	pthread_mutex_unlock(&philos->philo[i].mutex);
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
			philos->started = 0;
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

void	philo_sleep(t_philos *philos, int i)
{
	long	cur_time;
	long	period_of_time;

	if (philos->started && !philos->all_ate)
	{
		cur_time = get_time();
		period_of_time = get_time() + (philos->time_sleep);
		print_action(SLEEP, philos->philo[i].id, philos);
		smart_sleep(philos->time_sleep);
	}
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
	while (args->philos->started && !check_death(args->philos))
	{
		p_eat(args->philos, i);
		if (args->philos->all_ate)
			return (NULL);
		if (args->philos->started)
			philo_sleep(args->philos, i);
		if (args->philos->started)
			print_action(THINK, args->philos->philo[i].id, args->philos);
	}
	return (NULL);
}
