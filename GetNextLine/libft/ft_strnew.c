/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 21:59:09 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/23 18:09:12 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strnew(size_t size)
{
	char	*str;

	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (NULL);
	ft_memset(str, 0, size + 1);
	return (str);
}
