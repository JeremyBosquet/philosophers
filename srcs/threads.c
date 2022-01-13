/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:41:16 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/13 14:00:00 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	threads_start(t_philos *philos)
{
	int	i;

	i = 0;
	philos->start_time = get_time();
	while (i < philos->nb_philo)
	{
		dprintf(0, "Thread: %d\n", i);
		if (pthread_create(&philos->philo[i].thread, NULL,
				philo(philos, i), NULL) != 0)
			return ;
		pthread_detach(philos->philo[i].thread);
		usleep(100);
		i++;
	}
}
