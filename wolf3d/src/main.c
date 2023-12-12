/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 16:25:52 by phaydont          #+#    #+#             */
/*   Updated: 2019/08/24 02:33:36 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "wolf3d.h"
#include "libft.h"

static int	open_map(char *filename, t_display *dsp)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	dsp->map = parse_map(fd, 0, &(dsp->map_height));
	if (dsp->map == NULL)
	{
		write(1, "invalid map file.\n", 18);
		return (1);
	}
	close(fd);
	dsp->pos = get_start_position(dsp);
	if (dsp->pos.x == -1)
	{
		write(1, "missing starting point in map file.\n", 36);
		return (1);
	}
	return (0);
}

static void	init_variables(t_display *dsp, int width, int height)
{
	dsp->renderer = NULL;
	dsp->window = NULL;
	dsp->texture = NULL;
	dsp->width = width;
	dsp->height = height;
	dsp->dir = create_vec(0, -1);
	dsp->plane = create_vec(1, 0);
	dsp->movespeed = 0.1;
	dsp->wall_height = 1.0;
	dsp->exit = 0;
	dsp->pitch = sizeof(int) * width;
	dsp->pixels = NULL;
	dsp->textab = NULL;
	dsp->map = NULL;
}

static void	destroy_dsp(t_display *dsp)
{
	int	i;

	if (dsp->textab)
	{
		if (dsp->textab[0].data)
			free(dsp->textab[0].data);
		if (dsp->textab[1].data)
			free(dsp->textab[1].data);
		if (dsp->textab[2].data)
			free(dsp->textab[2].data);
		if (dsp->textab[3].data)
			free(dsp->textab[3].data);
		free(dsp->textab);
	}
	if (dsp->pixels)
		free(dsp->pixels);
	i = 0;
	if (dsp->map)
	{
		while (i < dsp->map_height)
			free(dsp->map[i++]);
		free(dsp->map);
	}
}

static int	display_init(t_display *dsp, int width, int height, char *filename)
{
	init_variables(dsp, width, height);
	if (open_map(filename, dsp) == 1)
		return (1);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (1);
	dsp->textab = malloc(sizeof(t_texture) * 4);
	if (dsp->textab == NULL)
		return (1);
	if (init_textures(dsp->textab) == 1)
		return (1);
	dsp->window = SDL_CreateWindow("wolf3d", 0, 0, width, height, 0);
	if (dsp->window == NULL)
		return (1);
	dsp->renderer = SDL_CreateRenderer(dsp->window, -1, 0);
	if (dsp->renderer == NULL)
		return (1);
	dsp->texture = SDL_CreateTexture(dsp->renderer, SDL_PIXELFORMAT_RGB888
			, SDL_TEXTUREACCESS_STREAMING, width, height);
	if (dsp->texture == NULL)
		return (1);
	dsp->pixels = malloc(sizeof(int) * width * height);
	if (dsp->pixels == NULL)
		return (1);
	return (0);
}

int			main(int argc, char **argv)
{
	t_display	dsp;

	if (argc == 2)
	{
		dsp.exit = display_init(&dsp, WIN_WIDTH, WIN_HEIGHT, argv[argc - 1]);
		while (dsp.exit == 0)
			event_loop(&dsp);
		if (dsp.renderer)
			SDL_DestroyRenderer(dsp.renderer);
		if (dsp.window)
			SDL_DestroyWindow(dsp.window);
		if (dsp.texture)
			SDL_DestroyTexture(dsp.texture);
		destroy_dsp(&dsp);
		SDL_Quit();
	}
	else
		write(1, "usage: ./wolf3d map_file\n", 25);
	return (0);
}
