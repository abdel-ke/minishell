/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amouassi <amouassi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 16:34:11 by amouassi          #+#    #+#             */
/*   Updated: 2021/04/12 16:45:30 by amouassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dest;
	unsigned char	*srce;
	size_t			i;

	i = 0;
	dest = (unsigned char *)dst;
	srce = (unsigned char *)src;
	if (!dest && !srce)
		return (NULL);
	if (dst > src)
	{
		while (len--)
		{
			*(unsigned char *)(dst + len) = *(unsigned char *)(src + len);
		}
		return (dst);
	}
	ft_memcpy(dest, srce, len);
	return (dest);
}
