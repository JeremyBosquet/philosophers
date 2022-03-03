/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:07:36 by jbosquet          #+#    #+#             */
/*   Updated: 2022/03/02 09:44:03 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	parsing(int argc, char **argv, t_args *philos)
{
	if ((argc == 5 || argc == 6))
	{
		philos->arg.nb_philo = ft_atoi_simplified(argv[1]);
		philos->arg.time_die = ft_atoi_simplified(argv[2]);
		philos->arg.time_eat = ft_atoi_simplified(argv[3]);
		philos->arg.time_sleep = ft_atoi_simplified(argv[4]);
		philos->arg.must_eat = -1;
		if (argc == 6)
			philos->arg.must_eat = ft_atoi_simplified(argv[5]);
		if (philos->arg.nb_philo <= 0 || philos->arg.time_die <= 0 || \
		philos->arg.time_eat <= 0 || philos->arg.time_sleep <= 0)
			return (0);
		return (1);
	}
	return (0);
}

static void	init_mutex(t_args *philos)
{
	pthread_mutex_init(&philos->arg.write_mutex, NULL);
	pthread_mutex_init(&philos->arg.mutex_dead, NULL);
	pthread_mutex_init(&philos->arg.mutex_time_eat, NULL);
	pthread_mutex_init(&philos->arg.mutex_finish, NULL);
}

int	init(t_args *philos)
{
	int	i;

	i = 0;
	philos->arg.time_start = get_time();
	philos->arg.stop = 0;
	philos->arg.nb_p_finish = 0;
	init_mutex(philos);
	while (i < philos->arg.nb_philo)
	{
		philos->philo[i].id = i + 1;
		philos->philo[i].last_eat = philos->arg.time_start;
		philos->philo[i].nb_eat = 0;
		philos->philo[i].finish = 0;
		philos->philo[i].fork_r = NULL;
		pthread_mutex_init(&philos->philo[i].fork_l, NULL);
		if (philos->arg.nb_philo == 1)
			return (1);
		if (i == philos->arg.nb_philo - 1)
			philos->philo[i].fork_r = &philos->philo[0].fork_l;
		else
			philos->philo[i].fork_r = &philos->philo[i + 1].fork_l;
		i++;
	}
	return (1);
}
