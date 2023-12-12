/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:52:55 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/21 20:50:05 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strncpy(char *dst, const char *src, size_t len)
{
	size_t i;
	size_t len_src;

	len_src = ft_strlen(src);
	if (!(dst || src))
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (i <= len_src)
			dst[i] = src[i];
		else
			dst[i] = '\0';
		i++;
	}
	return (dst);
}
