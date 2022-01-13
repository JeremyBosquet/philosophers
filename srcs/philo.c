/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:40:14 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/13 14:00:21 by jbosquet         ###   ########.fr       */
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
	print_action(EAT, philos->philo[i].id, philos);
	pthread_mutex_unlock(philos->philo[i].fork_l);
	pthread_mutex_unlock(&philos->philo[i].fork_r);
}

int	check_death(t_philos *philos)
{
	(void)philos;
	return (0);
}

void	*philo(t_philos *philos, int i)
{
	dprintf(1, "Philo: %d\n", philos->philo[i].id);
	// if (pthread_create(&philos->philo[i].thread, NULL,
	// 	philo(philos, i), NULL) != 0)
	// 	return (NULL);
	// if (philos->philo[i].id % 2)
	// 	usleep(10);
	// p_eat(philos, i);
	return (NULL);
}