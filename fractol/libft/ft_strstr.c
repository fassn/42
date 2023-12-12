/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 21:22:32 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/21 20:51:30 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 1;
	if (!(*needle))
		return ((char *)haystack);
	while (haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			while (haystack[i + n] == needle[n] && needle[n])
				n++;
			if (!needle[n])
				return ((char *)&haystack[i]);
		}
		i++;
	}
	return (NULL);
}
