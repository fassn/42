/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 19:54:06 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/21 20:53:42 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dest;
	const unsigned char	*source;
	unsigned char		ch;

	dest = (unsigned char *)dst;
	source = (const unsigned char *)src;
	ch = (unsigned char)c;
	while ((int)n--)
	{
		*dest++ = *source;
		if (*source == ch)
			return ((void *)dest);
		source++;
	}
	return (NULL);
}
