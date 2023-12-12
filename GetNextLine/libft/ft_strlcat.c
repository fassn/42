/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 18:48:33 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/21 20:50:42 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_src;
	size_t	j;

	len_src = ft_strlen(src);
	j = 0;
	while (dst[j] && j < size)
		j++;
	i = 0;
	while (src[i] && j + i + 1 < size)
	{
		dst[j + i] = src[i];
		i++;
	}
	if (j + i < size)
		dst[j + i] = '\0';
	return (j + len_src);
}
