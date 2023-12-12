/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:39:39 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/23 18:10:54 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		ft_len_n(int n)
{
	int len;

	len = 0;
	if (n < 0)
	{
		len = 1;
		n = -n;
	}
	while (n > 0)
	{
		len += 1;
		n /= 10;
	}
	return (len);
}

static char		*ft_add_nbr(int n, int len)
{
	char *str;

	if (!(str = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	str[len] = '\0';
	while (n > 0)
	{
		len--;
		str[len] = n % 10 + 48;
		n /= 10;
	}
	return (str);
}

char			*ft_itoa(int n)
{
	char	*str;

	if (n == -2147483648)
		str = ft_strdup("-2147483648");
	else if (n == 0)
		str = ft_strdup("0");
	else
		str = ft_add_nbr(n, ft_len_n(n));
	return (str);
}
