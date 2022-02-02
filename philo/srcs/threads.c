/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:41:16 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/02 11:00:47 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	threads_start(t_philos *philos)
{
	int		i;
	t_args	args;

	i = 0;
	args.philos = philos;
	while (i < philos->nb_philo)
	{
		args.i = i;
		if (pthread_create(&(philos->philo[i].thread), NULL,
				philo, &args))
			return ;
		pthread_detach(philos->philo[i].thread);
		usleep(100);
		i++;
	}
}
