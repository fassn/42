/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 18:28:25 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/21 20:56:39 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strequ(char const *s1, char const *s2)
{
	unsigned char *c1;
	unsigned char *c2;

	if (!s1 || !s2)
		return (-1);
	c1 = (unsigned char*)s1;
	c2 = (unsigned char*)s2;
	while (*c1 || *c2)
	{
		if (*c1 != *c2)
			return (0);
		c1++;
		c2++;
	}
	return (1);
}
