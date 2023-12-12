/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 13:43:43 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/27 16:36:29 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*source;
	unsigned char		*dest;
	size_t				i;

	source = (unsigned char *)src;
	dest = (unsigned char *)dst;
	i = 0;
	if (source < dest)
		while (len-- > 0)
			*(dest + len) = *(source + len);
	else
		while (i < len)
		{
			*(dest + i) = *(source + i);
			i++;
		}
	return (dst);
}
