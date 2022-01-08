/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 12:41:16 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/08 14:04:06 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    threads_start(t_philos *philos)
{
    int i;

    i = 0;
    philos->start_time = get_time();
    while (i < philos->nb_philo -1 )
    {
        dprintf(2, "Thread: %d\n", i);
        if (pthread_create(&philos->philo[i].thread, NULL, philo(philos, i), NULL))
            exit (EXIT_FAILURE);
        i++;
    }
}