/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 19:06:22 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/29 01:36:08 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// char	*ft_strchr(const char *s, int c)
// {
// 	unsigned char ch;
// 	unsigned char *str;

// 	ch = (unsigned char)c;
// 	str = (unsigned char *)s;
// 	if (*str == ch)
// 		return ((char *)str);
// 	while (*str != ch && *str)
// 	{
// 		str++;
// 		if (*str == ch)
// 			return ((char *)str);
// 	}
// 	return (NULL);
// }

char	*ft_strchr(const char *str, int c)
{
	int i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0' && str[i] != (char)c)
		i++;
	if (str[i] == (char)c)
		return ((char*)str + i);
	return (NULL);
}
