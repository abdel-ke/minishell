/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 15:42:06 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/12 16:48:58 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_char(char c, const char *set)
{
	int		i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_find_deb(char const *s, char const *set)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (!ft_is_char(s[i], set))
			break ;
		i++;
	}
	return (i);
}

static int	ft_find_fin(char const *s, char const *set)
{
	int		slen;
	int		fin;

	slen = ft_strlen(s) - 1;
	fin = slen;
	while (slen)
	{
		if (!ft_is_char(s[slen], set))
		{
			fin = slen;
			break ;
		}
		slen--;
	}
	return (fin);
}

char	*ft_strtrim(char const *s, char const *set)
{
	char	*str;
	int		start;
	int		len;

	if (s == NULL)
		return (NULL);
	start = ft_find_deb(s, set);
	len = ft_find_fin(s, set) - ft_find_deb(s, set) + 1;
	str = ft_substr(s, start, len);
	if (str == NULL || set == NULL)
		return (NULL);
	if (len < 0)
		return (ft_strdup(""));
	return (str);
}
