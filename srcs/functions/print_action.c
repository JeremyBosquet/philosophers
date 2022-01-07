/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 13:50:12 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/07 14:05:31 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(int action, int philo_id, t_philos *philos)
{
	suseconds_t	time;

	time = time_diff(philos->start_time, get_time());
	if (action == FORK)
		printf("%d %d %s\n", time, philo_id, "has taken a fork");
	else if (action == EAT)
		printf("%d %d %s\n", time, philo_id, "is eating");
	else if (action == SLEEP)
		printf("%d %d %s\n", time, philo_id, "is sleeping");
	else if (action == THINK)
		printf("%d %d %s\n", time, philo_id, "is thinking");
	else if (action == DIE)
		printf("%d %d %s\n", time, philo_id, "died");
}
