/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:36:03 by jbosquet          #+#    #+#             */
/*   Updated: 2022/03/01 19:14:15 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(long time)
{
	long	cur_time;
	long	period_of_time;

	cur_time = get_time();
	period_of_time = get_time() + (time);
	while (period_of_time > cur_time)
	{
		usleep(100);
		cur_time = get_time();
	}
}
