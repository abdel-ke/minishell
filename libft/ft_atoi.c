/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 14:07:59 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/12 16:38:05 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_subatoi(const char *str, int sign, int i)
{
	long int		res;
	long int		over;

	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		over = res;
		res = res * 10 + sign * (str[i] - '0');
		if (sign == 1 && res < over)
			return (-1);
		if (sign == -1 && res > over)
			return (0);
		i++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int			i;
	long int	res;
	int			sign;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	res = ft_subatoi(str, sign, i);
	return (res);
}
