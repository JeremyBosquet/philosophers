/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:10:03 by jbosquet          #+#    #+#             */
/*   Updated: 2022/03/02 09:23:18 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	wait_and_free_philo(t_args *philos)
{
	int	i;

	i = 0;
	while (!check_death2(philos))
		smart_sleep(1);
	while (i < philos->arg.nb_philo)
	{
		pthread_join(philos->philo[i].thread, NULL);
		i++;
	}
	pthread_mutex_destroy(&philos->arg.write_mutex);
	i = 0;
	while (++i < philos->arg.nb_philo)
	{
		pthread_mutex_destroy(&philos->philo[i].fork_l);
		i++;
	}
	free(philos->philo);
}

int	main(int argc, char **argv)
{
	t_args	philos;

	if (!(parsing(argc, argv, &philos)))
		return (ft_error("arguments\n"));
	philos.philo = malloc(sizeof(t_philo) * philos.arg.nb_philo);
	if (!philos.philo)
		return (ft_error("malloc\n"));
	if (!init(&philos) || !launch_threads(&philos))
	{
		free(philos.philo);
		return (0);
	}
	wait_and_free_philo(&philos);
}
