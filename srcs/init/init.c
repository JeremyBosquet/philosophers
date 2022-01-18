/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:27:37 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/18 12:13:40 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_philos(t_philos *philos)
{
	int	i;

	i = 1;
	philos->philo = malloc(sizeof(t_philo) * philos->nb_philo);
	if (!philos->philo)
		return ;
	while (i <= philos->nb_philo)
	{
		philos->philo[i - 1].id = i;
		philos->philo[i - 1].nb_eat = 0;
		philos->philo[i - 1].dead = 0;
		if (i != 1 && i != philos->nb_philo)
			philos->philo[i - 1].fork_l = &philos->philo[i - 2].fork_r;
		else if (i == philos->nb_philo)
		{
			philos->philo[i - 1].fork_l = &philos->philo[i - 2].fork_r;
			philos->philo[0].fork_l = &philos->philo[i - 1].fork_r;
		}
		pthread_mutex_init(&philos->philo[i - 1].fork_r, NULL);
		i++;
	}
}

static void	init_forks(t_philos *philos)
{
	int	i;

	i = 0;
	philos->fork = malloc(sizeof(t_fork) * philos->nb_philo);
	if (!philos->fork)
		return ;
	while (i < philos->nb_philo)
	{
		philos->fork[i].id = i;
		pthread_mutex_init(&philos->fork[i].mutex, NULL);
		i++;
	}
}

//EDIT ATOI !!

void	init(char **argv, int argc, t_philos *philos)
{
	philos->nb_philo = ft_atoi(argv[1]);
	philos->time_die = ft_atoi(argv[2]);
	philos->time_eat = ft_atoi(argv[3]);
	philos->time_sleep = ft_atoi(argv[4]);
	if (argc == 5)
		philos->must_eat = -1;
	else if (argc == 6)
		philos->must_eat = ft_atoi(argv[5]);
	if (philos->must_eat == 0)
		exit (EXIT_SUCCESS);
	philos->started = 0;
	philos->died = 0;
	philos->all_ate = 0;
	pthread_mutex_init(&philos->write_mutex, NULL);
	init_philos(philos);
	init_forks(philos);
}
