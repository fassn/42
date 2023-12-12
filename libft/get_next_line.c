/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:06:39 by cfargere          #+#    #+#             */
/*   Updated: 2019/01/28 13:59:30 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static char		*ft_append_char(char *line, char *buff, int *start)
{
	char	*str;
	int		i;

	str = ft_memalloc(ft_strlen(line) + ft_strlen(buff) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	if (line)
		while (line[i])
		{
			str[i] = line[i];
			i++;
		}
	while (buff[*start] != '\n' && buff[*start])
	{
		str[i] = buff[*start];
		i++;
		(*start)++;
	}
	str[i] = '\0';
	if (line)
		ft_strdel(&line);
	return (str);
}

static int		ft_read_input(const int fd, char **line, char **tmp, int *i)
{
	char		buf[BUFF_SIZE + 1];
	int			ret;

	while ((ret = read(fd, buf, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		buf[ret] = '\0';
		*i = 0;
		if (!(*line = ft_append_char(*line, buf, i)))
			return (-1);
		if (buf[(*i)++] == '\n')
		{
			if (buf[*i] != '\0')
				*tmp = ft_strdup(buf);
			return (1);
		}
	}
	if (*line)
		return (1);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char	*tmp;
	static int	i;
	int			ret;

	if (fd < 0 || !line)
		return (-1);
	*line = NULL;
	if (tmp)
	{
		if (tmp[i] != '\0')
			if (!(*line = ft_append_char(*line, tmp, &i)))
				return (-1);
		if (tmp[i++] == '\n')
			return (1);
		ft_strdel(&tmp);
	}
	if ((ret = ft_read_input(fd, line, &tmp, &i)) > 0)
		return (1);
	if (ret == -1)
		return (-1);
	return (0);
}
