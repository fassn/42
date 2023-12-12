/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:40:40 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/27 22:31:11 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

// static void			put_pixel_tmp(t_env *env, int x, int y, int color)
// {
// 	if (x >= W_WIDTH || y >= W_HEIGHT || x < 0 || y < 0)
// 		return ;
// 	env->pixels[y * W_WIDTH + x] = color;
// 	// printf("x %d y %d\n", x, y);
// }

// static int			get_text_color(int x, t_text *text, double height)
// {
// 	char	red;
// 	char	green;
// 	char	blue;
// 	int		adress;
// 	double	y;

// 	y = (int)((text->h) - height * text->h);
// 	adress = (y * text->w + x) * text->bpp / 8;
// 	printf("addres:%d\n", adress);
// 	blue = text->data[adress];
// 	green = text->data[adress + 1];
// 	red = text->data[adress + 2];
// 	return (red * 65536 + green * 256 + blue);
// }

/*
** @desc			renders the GUI
** @param env		main game structure
*/

void				draw_image(t_env *env, t_text text, int xp, int yp)
{
	int x;
	int y;
	// int	address;
	// int color;
	// char r, g, b;

	// printf("h %d w %d\n", text->h, text->w);
	x = -1;
	while (++x < text.w)
	{
		y = -1;
		while (++y < text.h)
		{
			get_rgb_color(env, text.str[y * text.w + x]);
			// printf("y - text-> + x %d\n", y * text->w + x);
			// address = ((text.h - y) * text.w + x) * 3;
			// r = text.data[address + 2];
			// g = text.data[address + 4];
			// b = text.data[address + 6];
			// color = r * 65536 + g * 256 + b;
			// color = text->data[(y * text->w + x)];
			// color = get_text_color(0, text, 0);
			// printf("color:%d\n", color);
			// if (color != -65793)
			if (text.str[y * text.w + x] & 0x00FFFFFF)
				pixel_put(env, x + xp, y + yp, env->color);
				// put_pixel_tmp(env, x + xp, y + yp, color);
		}
	}
	// printf("x + xp %d y + yp %d\n", x + xp, y + yp);
}

/*
** @desc			renders the weapon
** @param env		main game structure
** @param text		texture index
** @pos_x, pos_y	x, y screen placement coordinates for the weapon
*/

void				draw_weapon(t_env *env, t_text *text, int pos_x, int pos_y)
{
	int x;
	int y;
	int color;

	y = 0;
	while (y < text->h)
	{
		x = 0;
		while (x < text->w)
		{
			color = *(int*)(&text->str[y * text->w + x]);
			get_rgb_color(env, color);
			if (color & 0xFFFF0000 || color == 0)
			{
				pixel_put(env, x + pos_x, y + pos_y, env->color);
			}
			x++;
		}
		y++;
	}
}
