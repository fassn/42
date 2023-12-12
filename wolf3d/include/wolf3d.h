/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 15:00:00 by phaydont          #+#    #+#             */
/*   Updated: 2019/08/24 02:30:30 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# if __APPLE__
	#include "SDL.h"
# elif __linux__
	#include <SDL2/SDL.h>
# endif

# define WIN_WIDTH 1024
# define WIN_HEIGHT 768

typedef struct		s_vec
{
	double			x;
	double			y;
}					t_vec;

typedef struct		s_ray
{
	t_vec			pos;
	t_vec			delta;
	t_vec			step;
	t_vec			dist;
	int				posx;
	int				posy;
	char			wall;
	char			side;
	double			distance;
	double			wallx;
}					t_ray;

typedef struct		s_texture
{
	int				width;
	int				height;
	int				size;
	char			bpp;
	unsigned int	offset;
	unsigned char	*data;
}					t_texture;

typedef struct		s_display
{
	SDL_Renderer	*renderer;
	SDL_Window		*window;
	SDL_Texture		*texture;
	t_texture		*textab;
	int				*pixels;
	int				pitch;
	int				width;
	int				height;
	char			**map;
	int				map_width;
	int				map_height;
	t_vec			pos;
	t_vec			dir;
	t_vec			plane;
	double			movespeed;
	double			wall_height;
	char			exit;
}					t_display;

/*
** raycast.c
*/
void				raycast(t_display *dsp);

/*
** event_handler.c
*/
void				event_loop(t_display *dsp);

/*
** vectors.c
*/
t_vec				create_vec(double x, double y);

/*
** player.c
*/
void				rotation(t_display *dsp, double angle);
void				move(t_display *dsp, double distance);
void				translate(t_display *dsp, double distance);

/*
** draw.c
*/
void				display(t_display *dsp);
void				put_pixel(unsigned int x, unsigned int y, int color,
					t_display *dsp);
void				draw_column(t_ray *ray, int x, int texx, t_display *dsp);

/*
** texture_parser.c
*/
int					init_textures(t_texture *textab);

/*
** parser.c
*/
char				**parse_map(int fd, int index, int *height);
t_vec				get_start_position(t_display *dsp);

#endif
