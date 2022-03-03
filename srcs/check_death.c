/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:37:52 by jbosquet          #+#    #+#             */
/*   Updated: 2022/03/02 09:39:36 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death2(t_args *philos)
{
	pthread_mutex_lock(&philos->arg.mutex_dead);
	if (philos->arg.stop)
	{
		pthread_mutex_unlock(&philos->arg.mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philos->arg.mutex_dead);
	return (0);
}

int	check_death(t_philo *philo, int i)
{
	pthread_mutex_lock(&philo->arg->mutex_dead);
	if (i)
		philo->arg->stop = i;
	if (philo->arg->stop)
	{
		pthread_mutex_unlock(&philo->arg->mutex_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo->arg->mutex_dead);
	return (0);
}
