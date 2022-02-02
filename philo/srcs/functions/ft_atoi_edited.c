/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_edited.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 13:10:49 by jbosquet          #+#    #+#             */
/*   Updated: 2022/02/02 11:11:00 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_error(void)
{
	write(2, "Error: arguments\n", 17);
	return (0);
}

int	ft_atoi_simplified(const char *str)
{
	int				i;
	int				neg;
	unsigned int	n;

	i = 0;
	n = 0;
	neg = 1;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
			i++;
	if (str[i] == '+' || str[i] == '-')
		if (str[i++] == '-')
			return (ft_error());
	if (i == (int)ft_strlen(str))
		return (ft_error());
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (10 * n) + (str[i++] - 48);
		if ((n > 2147483647 && neg == 1) || (n > 2147483648 && neg == -1))
			return (ft_error());
	}
	if (i == 0 || i != (int)ft_strlen(str))
		return (ft_error());
	return ((int)n * neg);
}
