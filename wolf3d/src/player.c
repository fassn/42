/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phaydont <phaydont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 12:19:06 by phaydont          #+#    #+#             */
/*   Updated: 2019/06/22 18:40:23 by phaydont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"
#include <math.h>

void	rotation(t_display *dsp, double angle)
{
	double temp;

	angle = angle * M_PI / 180;
	temp = dsp->dir.x * cos(angle) - dsp->dir.y * sin(angle);
	dsp->dir.y = dsp->dir.x * sin(angle) + dsp->dir.y * cos(angle);
	dsp->dir.x = temp;
	temp = dsp->plane.x * cos(angle) - dsp->plane.y * sin(angle);
	dsp->plane.y = dsp->plane.x * sin(angle) + dsp->plane.y * cos(angle);
	dsp->plane.x = temp;
}

void	move(t_display *dsp, double distance)
{
	double	movex;
	double	movey;
	double	temp;

	temp = dsp->pos.x;
	movex = dsp->pos.x + distance * dsp->dir.x * dsp->movespeed;
	movey = dsp->pos.y + distance * dsp->dir.y * dsp->movespeed;
	if (!(movex < 0 || movex >= ft_strlen(dsp->map[(int)dsp->pos.y])
		|| dsp->map[(int)dsp->pos.y][(int)movex] != '0'))
		dsp->pos.x = movex;
	if (!(movey < 0 || movey > dsp->map_height
		|| temp >= ft_strlen(dsp->map[(int)movey])
		|| dsp->map[(int)movey][(int)dsp->pos.x] != '0'))
		dsp->pos.y = movey;
}

void	translate(t_display *dsp, double distance)
{
	double	movex;
	double	movey;
	double	temp;

	temp = dsp->pos.x;
	movex = dsp->pos.x + distance * dsp->dir.y * dsp->movespeed;
	movey = dsp->pos.y + distance * -dsp->dir.x * dsp->movespeed;
	if (!(movex < 0 || movex >= ft_strlen(dsp->map[(int)dsp->pos.y])
		|| dsp->map[(int)dsp->pos.y][(int)movex] != '0'))
		dsp->pos.x = movex;
	if (!(movey < 0 || movey > dsp->map_height
		|| temp >= ft_strlen(dsp->map[(int)movey])
		|| dsp->map[(int)movey][(int)dsp->pos.x] != '0'))
		dsp->pos.y = movey;
}
