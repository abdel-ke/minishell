/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 11:49:11 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/22 11:49:31 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *str, char *to_find)
{
	int		i;
	int		j;
	int		k;
	char	*s;

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		k = i;
		while (to_find[j] != '\0')
		{
			if (str[k] != to_find[j])
				break ;
			k++;
			j++;
		}
		if (to_find[j] == '\0')
		{
			s = &str[k - j];
			return (s);
		}
		i++;
	}
	return (0);
}
