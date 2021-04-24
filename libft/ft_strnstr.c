/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 11:41:45 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/12 16:48:04 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_str(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		k;
	const char	*s;

	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		k = i;
		while (needle[j] != '\0' && k < len)
		{
			if (haystack[k] != needle[j])
				break ;
			k++;
			j++;
		}
		if (needle[j] == '\0')
		{
			s = &haystack[k - j];
			return ((char *)s);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	char		*str;

	i = 0;
	if (haystack == NULL && needle != NULL && len == 0)
		return (NULL);
	if (needle[i] == '\0')
		return ((char *)haystack);
	str = ft_str(haystack, needle, len);
	return (str);
}
