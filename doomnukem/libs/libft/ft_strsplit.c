/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/19 13:00:53 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/26 05:59:15 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t			ft_count_words(char const *s, char c)
{
	size_t words;

	words = 0;
	while (*s)
	{
		if (*s != c && *s)
			words += 1;
		while (*s != c && *s)
			s++;
		if (*s)
			s++;
	}
	return (words);
}

static void				ft_populate_tab(char const *s, char c, char **tab,
		size_t words)
{
	int		i;
	int		j;
	int			start;
	int			end;
	i = 0;
	j = 0;
	while (s[i] != '\0' && words > 0)
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			end = i;
			tab[j] = ft_strsub(s, start, end - start);
			j++;
			words--;
		}
		i++;
	}
	tab[j] = 0;
}

char					**ft_strsplit(char const *s, char c)
{
	char		**tab;
	size_t		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	if (!(tab = (char **)malloc((words + 1) * sizeof(char *))))
		return (NULL);
	ft_populate_tab(s, c, tab, words);
	return (tab);
}
