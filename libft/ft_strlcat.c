/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 16:08:31 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/12 16:47:17 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		srclen;
	size_t		dstlen;
	size_t		i;

	srclen = ft_strlen(src);
	if (dst == NULL && size == 0)
		return (srclen);
	dstlen = ft_strlen(dst);
	if (dstlen >= size)
		return (srclen + size);
	else if (dstlen < size)
	{
		i = 0;
		while (src[i] && i < (size - dstlen - 1))
		{
			dst[dstlen + i] = src[i];
			i++;
		}
		dst[dstlen + i] = '\0';
	}
	return (srclen + dstlen);
}
