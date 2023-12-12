/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:08:21 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/21 20:47:57 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char ch;
	unsigned char *str;

	ch = (unsigned char)c;
	str = (unsigned char *)s;
	while ((int)n--)
	{
		if (*str == ch)
			return ((void *)str);
		str++;
	}
	return (NULL);
}
