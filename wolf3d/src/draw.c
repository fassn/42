/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 12:12:01 by phaydont          #+#    #+#             */
/*   Updated: 2019/08/24 02:34:17 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		display(t_display *dsp)
{
	SDL_RenderClear(dsp->renderer);
	SDL_UpdateTexture(dsp->texture, NULL, dsp->pixels, dsp->pitch);
	SDL_RenderCopy(dsp->renderer, dsp->texture, NULL, NULL);
	SDL_RenderPresent(dsp->renderer);
}

void		put_pixel(unsigned int x, unsigned int y, int color, t_display *dsp)
{
	if (x < (unsigned int)dsp->width && y < (unsigned int)dsp->height)
		dsp->pixels[y * dsp->width + x] = color;
}

static int	get_tex_color(t_display *dsp, int x, double height, int side)
{
	char	red;
	char	green;
	char	blue;
	int		adress;
	double	y;

	y = (int)((dsp->textab[side].height) - height * dsp->textab[side].height);
	adress = (y * dsp->textab[side].width + x) * dsp->textab[side].bpp / 8;
	blue = dsp->textab[side].data[adress];
	green = dsp->textab[side].data[adress + 1];
	red = dsp->textab[side].data[adress + 2];
	return (red * 65536 + green * 256 + blue);
}

void		draw_column(t_ray *ray, int x, int texx, t_display *dsp)
{
	int		i;
	double	height;
	int		top;
	int		bottom;
	int		color;

	height = dsp->wall_height * dsp->height / ray->distance;
	top = dsp->height / 2 - height / 2;
	bottom = top + height;
	i = 0;
	while (i < dsp->height)
	{
		if (i <= top)
			color = 0x004499;
		else if (i < bottom)
			color = get_tex_color(dsp, texx, (i - top) / height, ray->side);
		else
			color = 0x774422;
		put_pixel(x, i, color, dsp);
		i++;
	}
}
