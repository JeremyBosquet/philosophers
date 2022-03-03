/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:35:46 by jbosquet          #+#    #+#             */
/*   Updated: 2022/03/02 09:42:46 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_action(char *action, t_philo *philo)
{
	suseconds_t	time;

	time = -1;
	time = get_time() - philo->arg->time_start;
	if (time >= 0 && !check_death(philo, 0))
		if (time <= 2147483647)
			printf("%d %d %s", time, philo->id, action);
}
