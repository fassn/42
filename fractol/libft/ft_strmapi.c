/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 17:58:13 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/23 18:09:28 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*str;
	size_t			len;
	size_t			i;
	unsigned int	j;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	if (!(str = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	j = 0;
	while (i < len)
	{
		str[i++] = f(j, s[j]);
		j++;
	}
	str[i] = '\0';
	return (str);
}
