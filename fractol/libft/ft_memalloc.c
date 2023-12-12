/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:28:39 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/23 18:09:08 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*mem;

	if (size > 2147483647)
		return (NULL);
	if (!(mem = malloc(size + 1)))
		return (NULL);
	ft_bzero(mem, size + 1);
	return (mem);
}
