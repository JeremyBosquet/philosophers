/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:20:18 by jbosquet          #+#    #+#             */
/*   Updated: 2022/03/02 09:52:15 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*is_dead(void	*data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	smart_sleep(philo->arg->time_die + 1);
	pthread_mutex_lock(&philo->arg->mutex_time_eat);
	pthread_mutex_lock(&philo->arg->mutex_finish);
	if (check_death(philo, 0) == 0 && philo->finish == 0 \
	&& ((get_time() - philo->last_eat) >= (philo->arg->time_die)))
	{
		pthread_mutex_unlock(&philo->arg->mutex_time_eat);
		pthread_mutex_unlock(&philo->arg->mutex_finish);
		pthread_mutex_lock(&philo->arg->write_mutex);
		print_action("died\n", philo);
		pthread_mutex_unlock(&philo->arg->write_mutex);
		check_death(philo, 1);
	}
	pthread_mutex_unlock(&philo->arg->mutex_time_eat);
	pthread_mutex_unlock(&philo->arg->mutex_finish);
	return (NULL);
}

void	*thread(void *data)
{
	t_philo					*philo;

	philo = (t_philo *)data;
	if (philo->id % 2 == 0)
		usleep(700);
	while (check_death(philo, 0) == 0)
	{
		pthread_create(&philo->thread_death, NULL, is_dead, data);
		routine(philo);
		pthread_detach(philo->thread_death);
		if ((int)++philo->nb_eat == philo->arg->must_eat)
		{
			pthread_mutex_lock(&philo->arg->mutex_finish);
			philo->finish = 1;
			philo->arg->nb_p_finish++;
			if (philo->arg->nb_p_finish == philo->arg->nb_philo)
			{
				pthread_mutex_unlock(&philo->arg->mutex_finish);
				check_death(philo, 2);
			}
			pthread_mutex_unlock(&philo->arg->mutex_finish);
			return (NULL);
		}
	}
	return (NULL);
}

int	launch_threads(t_args *philos)
{
	int	i;

	i = 0;
	while (i < philos->arg.nb_philo)
	{
		philos->philo[i].arg = &philos->arg;
		if (pthread_create(&philos->philo[i].thread, NULL, thread, \
		&philos->philo[i]) != 0)
			return (ft_error("pthread create\n"));
		usleep(100);
		i++;
	}
	return (1);
}
