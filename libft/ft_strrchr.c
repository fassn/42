/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:48:58 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/21 20:51:14 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	ch;
	unsigned char	*str;
	int				len;

	ch = (unsigned char)c;
	str = (unsigned char *)s;
	while (*str)
		str++;
	len = str - (unsigned char *)s;
	if (*str == ch)
		return ((char *)str);
	while (len--)
	{
		str--;
		if (*str == ch)
			return ((char *)str);
	}
	return (NULL);
}
