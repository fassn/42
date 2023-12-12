/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:24:37 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/23 18:10:19 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t		ft_find_start_trimmed_str(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t')
		i++;
	return (i);
}

static size_t		ft_find_len_trimmed_str(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	while (s[i] == ' ' || s[i] == '\n' || s[i] == '\t' ||
			s[i] == '\0')
		i--;
	if (i < 0)
		return (0);
	return (i + 1 - ft_find_start_trimmed_str(s));
}

char				*ft_strtrim(char const *s)
{
	char	*str;
	int		i;
	int		j;
	int		len_trimmed;

	if (!s)
		return (NULL);
	len_trimmed = ft_find_len_trimmed_str(s);
	if (!(str = (char *)malloc((len_trimmed + 1) * sizeof(char))))
		return (NULL);
	j = ft_find_start_trimmed_str(s);
	i = 0;
	while (i < len_trimmed)
		str[i++] = s[j++];
	str[i] = '\0';
	return (str);
}
