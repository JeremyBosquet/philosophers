/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:39:22 by jbosquet          #+#    #+#             */
/*   Updated: 2022/03/02 09:36:49 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_think(t_philo *philo)
{
	smart_sleep(philo->arg->time_sleep);
	pthread_mutex_lock(&philo->arg->write_mutex);
	print_action("is thinking\n", philo);
	pthread_mutex_unlock(&philo->arg->write_mutex);
}

void	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->write_mutex);
	print_action("is sleeping\n", philo);
	pthread_mutex_unlock(&philo->arg->write_mutex);
}

void	routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork_l);
	pthread_mutex_lock(&philo->arg->write_mutex);
	print_action("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->arg->write_mutex);
	if (!philo->fork_r)
	{
		smart_sleep(philo->arg->time_die * 2);
		return ;
	}
	pthread_mutex_lock(philo->fork_r);
	pthread_mutex_lock(&philo->arg->write_mutex);
	print_action("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->arg->write_mutex);
	pthread_mutex_lock(&philo->arg->write_mutex);
	print_action("is eating\n", philo);
	pthread_mutex_lock(&philo->arg->mutex_time_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->arg->mutex_time_eat);
	pthread_mutex_unlock(&philo->arg->write_mutex);
	smart_sleep(philo->arg->time_eat);
	pthread_mutex_unlock(philo->fork_r);
	pthread_mutex_unlock(&philo->fork_l);
	philo_sleep(philo);
	philo_think(philo);
}
