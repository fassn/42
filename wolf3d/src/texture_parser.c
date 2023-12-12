/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 11:51:53 by phaydont          #+#    #+#             */
/*   Updated: 2019/07/04 17:09:05 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "wolf3d.h"
#include <stdlib.h>

static int	parse_header(int fd, t_texture *texture)
{
	char	*buffer;

	buffer = malloc(sizeof(char) * 54);
	if (buffer == NULL)
		return (1);
	if (read(fd, buffer, 54) == 54)
	{
		if (buffer[0] != 'B' || buffer[1] != 'M')
		{
			free(buffer);
			return (1);
		}
		texture->offset = *(unsigned int *)&(buffer[10]);
		texture->width = *(int *)&(buffer[18]);
		texture->height = *(int *)&(buffer[22]);
		if (texture->height < 0)
			texture->height *= -1;
		texture->bpp = buffer[28];
		texture->size = texture->width * texture->height * texture->bpp / 8;
	}
	free(buffer);
	if (texture->bpp != 24 || texture->height < 0 || texture->width < 0
		|| texture->height > 4096 || texture->width > 4096)
		return (1);
	return (0);
}

static int	skip_header(int fd, t_texture *texture)
{
	char	*skip;
	int		lu;

	if (texture->offset < 54)
		return (1);
	else if (texture->offset == 54)
		return (0);
	skip = malloc(sizeof(char) * texture->offset - 54);
	if (skip == NULL)
		return (1);
	lu = read(fd, skip, texture->offset - 54);
	free(skip);
	if (lu != (int)texture->offset - 54)
		return (1);
	return (0);
}

static int	parse_data(int fd, t_texture *texture)
{
	int	index;
	int	line;

	texture->data = malloc(sizeof(char) * texture->size);
	if (texture->data == NULL)
		return (1);
	index = 0;
	line = texture->width * texture->bpp / 8;
	while (read(fd, texture->data + index, line) == line)
		index += line;
	if (index != texture->size)
	{
		free(texture->data);
		texture->data = NULL;
		return (1);
	}
	return (0);
}

static int	parse_bmp(char *filename, t_texture *texture)
{
	int			fd;
	static int	color = 0;

	fd = open(filename, O_RDONLY);
	if (fd > 0)
	{
		if (parse_header(fd, texture) == 0)
			if (skip_header(fd, texture) == 0)
				if (parse_data(fd, texture) == 0)
				{
					close(fd);
					return (0);
				}
	}
	texture->height = 1;
	texture->width = 1;
	texture->data = malloc(sizeof(char) * 3);
	texture->data[2] = color - 1;
	texture->data[1] = 127;
	texture->data[0] = color / 2;
	color += 64;
	close(fd);
	return (0);
}

int			init_textures(t_texture *textab)
{
	int	ret;

	ret = 0;
	textab[0].data = NULL;
	textab[1].data = NULL;
	textab[2].data = NULL;
	textab[3].data = NULL;
	if (ret == 0)
		ret = parse_bmp("./assets/Wall/Grey10.bmp", &(textab[0]));
	if (ret == 0)
		ret = parse_bmp("./assets/Wall/BR2.bmp", &(textab[1]));
	if (ret == 0)
		ret = parse_bmp("./assets/Wall/Orange13.bmp", &(textab[2]));
	if (ret == 0)
		ret = parse_bmp("./assets/Wall/Brown17.bmp", &(textab[3]));
	if (ret == 1)
		write(1, "invalid texture(s) found in ./assets/Wall/.\n", 44);
	return (ret);
}
