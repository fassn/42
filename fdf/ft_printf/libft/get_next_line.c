/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlombard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:06:11 by hlombard          #+#    #+#             */
/*   Updated: 2019/04/01 13:02:07 by hlombard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/libft.h"
#include "../ft_printf.h"

static size_t		ft_strlen2(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == '\0' && str[i + 1] && str[i + 1] == '\0')
			return (0);
		i++;
	}
	return (i);
}

static void			line_input(char **stock, char **line)
{
	size_t	len;
	char	*tmp;
	char	*ptr;

	tmp = NULL;
	ptr = ft_strchr(*stock, '\n');
	len = ft_strlen2(*stock);
	if (ptr)
	{
		*line = ft_strsub(*stock, 0, len);
		tmp = *stock;
		*stock = ft_strdup(ptr + 1);
		free(tmp);
	}
	if (!(*stock))
		ft_strdel(stock);
}

static void			stock_increase(char **stock, char *buf, int ret)
{
	char	*tmp;

	buf[ret] = '\0';
	if (buf[ret - 1] == '\0' && buf[ret - 2] == '\0')
	{
		ft_printf("{red}{bold}/dev/zero is invalid !{eoc}\n");
		exit(0);
	}
	tmp = *stock;
	*stock = ft_strjoin(*stock, buf);
	ft_strdel(&tmp);
}

int					get_next_line(const int fd, char **line)
{
	int				ret;
	char			*buf;
	static char		*stock = NULL;

	buf = ft_strnew(BUFF_SIZE);
	if (read(fd, buf, 0) == -1 || fd < 0 || !line || BUFF_SIZE < 1)
	{
		ft_strdel(&buf);
		return (-1);
	}
	if (!stock)
		stock = ft_strnew(BUFF_SIZE);
	while (ft_strchr(stock, '\n') == NULL && (ret = read(fd, buf, BUFF_SIZE)))
		stock_increase(&stock, buf, ret);
	ft_strdel(&buf);
	if ((ret == 0) && ft_strchr(stock, '\n') == NULL)
	{
		*line = stock;
		if (!*stock)
			return (0);
		stock = NULL;
		return (1);
	}
	line_input(&stock, line);
	return (1);
}
