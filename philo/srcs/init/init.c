/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:27:37 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/02 11:18:20 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_hard_one(int time_die)
{
	write(1, "0 1 has taken a fork\n", 21);
	smart_sleep(time_die);
	printf("%d 1 died\n", time_die);
	exit(EXIT_FAILURE);
}

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

int	init(char **argv, int argc, t_philos *philos)
{
	philos->nb_philo = ft_atoi_simplified(argv[1]);
	philos->time_die = ft_atoi_simplified(argv[2]);
	if (!philos->nb_philo || !philos->time_die)
		return (0);
	philos->time_eat = ft_atoi_simplified(argv[3]);
	philos->time_sleep = ft_atoi_simplified(argv[4]);
	if (!philos->time_eat || !philos->time_sleep)
		return (0);
	if (philos->nb_philo == 1)
		ft_hard_one(philos->time_die);
	if (argc == 5)
		philos->must_eat = -1;
	else if (argc == 6)
		philos->must_eat = ft_atoi_simplified(argv[5]);
	if (philos->must_eat == 0)
		return (0);
	philos->started = 0;
	philos->died = 0;
	philos->all_ate = 0;
	pthread_mutex_init(&philos->write_mutex, NULL);
	init_philos(philos);
	init_forks(philos);
	return (1);
}
