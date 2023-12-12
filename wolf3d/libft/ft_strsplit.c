/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:47:54 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/27 16:36:29 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	ft_count_words(char const *s, char c)
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

static void		ft_populate_tab(char const *s, char c, char **tab, size_t words)
{
	size_t	i;
	size_t	j;
	int		start;
	int		end;

	i = 0;
	j = 0;
	while (s[i] && words > 0)
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

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	if (!(tab = (char **)malloc((words + 1) * sizeof(*tab))))
		return (NULL);
	ft_populate_tab(s, c, tab, words);
	return (tab);
}
