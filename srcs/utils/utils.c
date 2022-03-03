/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:51:09 by jbosquet          #+#    #+#             */
/*   Updated: 2022/03/02 09:42:17 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
			return (0);
	if (i == (int)ft_strlen((char *)str))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (10 * n) + (str[i++] - 48);
		if ((n > 2147483647 && neg == 1) || (n > 2147483648 && neg == -1))
			return (0);
	}
	if (i == 0 || i != (int)ft_strlen((char *)str))
		return (0);
	return ((int)n * neg);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *str, int fd)
{
	int	i;

	i = 0;
	if (fd >= 0)
	{
		while (str && str[i])
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
}
