/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:40:39 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/21 20:50:58 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char ch;
	unsigned char *str;

	ch = (unsigned char)c;
	str = (unsigned char *)s;
	if (*str == ch)
		return ((char *)str);
	while (*str != ch && *str)
	{
		str++;
		if (*str == ch)
			return ((char *)str);
	}
	return (NULL);
}
