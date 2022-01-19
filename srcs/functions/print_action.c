/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:50:12 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/19 17:08:11 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(int action, int philo_id, t_philos *philos)
{
	suseconds_t	time;

	if (!philos->all_ate)
	{
		pthread_mutex_lock(&philos->write_mutex);
		time = time_diff(philos->start_time, get_time());
		if (action == FORK && !philos->all_ate)
			printf("%d %d %s\n", time, philo_id, "has taken a fork");
		else if (action == EAT && !philos->all_ate)
			printf("%d %d %s\n", time, philo_id, "is eating");
		else if (action == SLEEP && !philos->all_ate)
			printf("%d %d %s\n", time, philo_id, "is sleeping");
		else if (action == THINK && !philos->all_ate)
			printf("%d %d %s\n", time, philo_id, "is thinking");
		else if (action == DIE)
		{
			printf("%d %d %s\n", time, philo_id, "died");
			return ;
		}
		pthread_mutex_unlock(&philos->write_mutex);
	}
	else
		pthread_mutex_lock(&philos->write_mutex);
}
