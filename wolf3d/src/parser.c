/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 16:37:52 by cfargere          #+#    #+#             */
/*   Updated: 2019/07/04 16:57:08 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "wolf3d.h"

char	**parse_map(int fd, int index, int *height)
{
	char	**map;
	char	*line;
	int		ret;

	if ((ret = get_next_line(fd, &line)) <= 0)
	{
		if (ret < 0)
			return (NULL);
		*height = index;
		return (malloc(sizeof(char *) * index));
	}
	map = parse_map(fd, index + 1, height);
	if (map != NULL)
		map[index] = ft_strdup(line);
	free(line);
	return (map);
}

t_vec	get_start_position(t_display *dsp)
{
	int x;
	int y;

	y = 0;
	while (y < dsp->map_height)
	{
		x = 0;
		while (dsp->map[y][x] != '\0')
		{
			if (dsp->map[y][x] == 'x')
			{
				dsp->map[y][x] = '0';
				return (create_vec(x + 0.5, y + 0.5));
			}
			x++;
		}
		y++;
	}
	return (create_vec(-1, -1));
}
