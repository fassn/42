/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:14:46 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/26 06:09:30 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

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
