/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 11:58:26 by jbosquet          #+#    #+#             */
/*   Updated: 2022/01/28 11:58:36 by jbosquet         ###   ########.fr       */
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
