/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:10:03 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/28 13:44:15 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(t_philos *philos)
{
	int	i;

	i = 0;
	free(philos->philo);
	free(philos->fork);
	while (i < philos->nb_philo)
	{
		pthread_mutex_destroy(&philos->philo[i].mutex);
		pthread_join(philos->philo[i++].thread, NULL);
	}
	pthread_mutex_destroy(&philos->write_mutex);
}

int	main(int argc, char **argv)
{
	t_philos	philos;

	if (argc != 5 && argc != 6)
		return (printf("Error: arguments.\n") * 0 + 1);
	init(argv, argc, &philos);
	threads_start(&philos);
	while (1)
	{
		if (philos.must_eat != -1 && check_nb_eat(&philos))
		{
			free_philo(&philos);
			return (EXIT_FAILURE);
		}
		else if (!philos.started)
		{
			free_philo(&philos);
			return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
