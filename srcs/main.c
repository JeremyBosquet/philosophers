/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 13:10:03 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/18 15:14:44 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/*
• The program should take the following arguments: 
	./philo <nb_philo> <time_die> <time_eat> <time_sleep> [nb_time_philo_must_eat]

		◦ nb_philo: is the number of philosophers and also the number of forks.
		◦ time_die: is in milliseconds, if a philosopher doesn’t start eating ’time_to_die’ milliseconds after starting their last meal or the beginning of the simulation, it dies.
		◦ time_eat: is in milliseconds and is the time it takes for a philosopher to eat. During that time they will need to keep the two forks.
		◦ time_sleep: is in milliseconds and is the time the philosopher will spend sleeping.
		◦ nb_time_philo_must_eat: argument is optional, if all philosophers eat at least ’nnb_time_philo_must_eat’ the
			simulation will stop. If not specified, the simulation will stop only at the death of a philosopher.

• Each philosopher should be given a number from 1 to ’nb_philo’.

• Philosopher number 1 is next to philosopher number ’nb_philo’.
Any other philosopher with the number N is seated between philosopher N - 1 and philosopher N + 1.

Faire le lancement des Threads %2 pour eviter que tout le monde se vol les fourchettes

*/

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
		return (printf("Erreur: arguments non valide.\n"));
	init(argv, argc, &philos);
	printf("Game init:\n");
	printf("nb_philo  : %d\n", philos.nb_philo);
	printf("time_die  : %d\n", philos.time_die);
	printf("time_eat  : %d\n", philos.time_eat);
	printf("time_sleep: %d\n", philos.time_sleep);
	printf("must_eat  : %d\n", philos.must_eat);
	printf("============================\n");
	threads_start(&philos);
	while (1)
	{
		if (check_nb_eat(&philos) || philos.died)
		{
			free_philo(&philos);
			exit(EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
