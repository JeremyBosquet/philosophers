/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:41:16 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/17 13:25:37 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	threads_start(t_philos *philos)
{
	int		i;
	t_args	args;

	i = 0;
	args.philos = philos;
	philos->start_time = get_time();
	while (i < philos->nb_philo)
	{
		args.i = i;
		//dprintf(0, "Thread: %d\n", i);
		if (pthread_create(&(philos->philo[i].thread), NULL,
				philo, &args) != 0)
			return ;
		pthread_detach(philos->philo[i].thread);
		usleep(100);
		i++;
	}
}
