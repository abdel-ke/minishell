/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 13:17:20 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/12 16:44:09 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count(int n)
{
	int		count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = n * -1;
	}
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*str;
	int			i;
	int long	nb;

	nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	str = (char *)malloc((ft_count(n) + 1) * sizeof(char));
	if (str == NULL)
		return (NULL);
	i = ft_count(n) - 1;
	if (nb < 0)
	{
		str[0] = '-';
		nb = nb * -1;
	}
	while (nb != 0)
	{
		str[i] = nb % 10 + '0';
		nb = nb / 10;
		i--;
	}
	str[ft_count(n)] = '\0';
	return (str);
}
