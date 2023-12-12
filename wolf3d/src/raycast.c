/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/24 15:10:46 by phaydont          #+#    #+#             */
/*   Updated: 2019/08/24 02:34:01 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "libft.h"

static void	set_wallx(t_ray *ray, t_display *dsp)
{
	if (ray->side % 2 == 0)
		ray->wallx = dsp->pos.y + ray->distance * ray->pos.y;
	else
		ray->wallx = dsp->pos.x + ray->distance * ray->pos.x;
	ray->wallx -= (int)ray->wallx;
	if (ray->side == 1 || ray->side == 2)
		ray->wallx = 1 - ray->wallx;
}

static void	set_ray_distance(t_ray *ray, t_display *dsp)
{
	if (ray->side == 0)
	{
		ray->distance = (ray->posx - dsp->pos.x + (1 - ray->step.x) / 2);
		ray->distance /= ray->pos.x;
	}
	else
	{
		ray->distance = (ray->posy - dsp->pos.y + (1 - ray->step.y) / 2);
		ray->distance /= ray->pos.y;
	}
	if ((ray->step.x < 0 && ray->side == 0)
		|| (ray->step.y < 0 && ray->side == 1))
		ray->side += 2;
}

static void	set_ray_step(t_ray *ray, t_display *dsp)
{
	if (ray->pos.x < 0)
	{
		ray->step.x = -1;
		ray->dist.x = (dsp->pos.x - (int)dsp->pos.x) * ray->delta.x;
	}
	else
	{
		ray->step.x = 1;
		ray->dist.x = ((int)dsp->pos.x + 1 - dsp->pos.x) * ray->delta.x;
	}
	if (ray->pos.y < 0)
	{
		ray->step.y = -1;
		ray->dist.y = (dsp->pos.y - (int)dsp->pos.y) * ray->delta.y;
	}
	else
	{
		ray->step.y = 1;
		ray->dist.y = ((int)dsp->pos.y + 1 - dsp->pos.y) * ray->delta.y;
	}
}

static void	cast_ray(t_ray *ray, t_display *dsp)
{
	ray->posx = (int)dsp->pos.x;
	ray->posy = (int)dsp->pos.y;
	ray->side = -1;
	while (dsp->map[ray->posy][ray->posx] == '0')
	{
		if (ray->dist.x < ray->dist.y)
		{
			ray->dist.x += ray->delta.x;
			ray->posx += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->dist.y += ray->delta.y;
			ray->posy += ray->step.y;
			ray->side = 1;
		}
		if (ray->posx < 0 || ray->posy < 0 || ray->posy > dsp->map_height - 1
			|| ray->posx >= (int)ft_strlen(dsp->map[(int)ray->posy]))
			return ;
	}
}

void		raycast(t_display *dsp)
{
	int		i;
	double	planex;
	t_ray	ray;
	int		texx;

	i = 0;
	while (i < dsp->width)
	{
		planex = (2 * (double)i / (dsp->width - 1) - 1);
		ray.pos.x = dsp->dir.x + dsp->plane.x * planex;
		ray.pos.y = dsp->dir.y + dsp->plane.y * planex;
		ray.delta.x = fabs(1.0 / ray.pos.x);
		ray.delta.y = fabs(1.0 / ray.pos.y);
		set_ray_step(&ray, dsp);
		cast_ray(&ray, dsp);
		set_ray_distance(&ray, dsp);
		set_wallx(&ray, dsp);
		texx = ray.wallx * (dsp->textab[(int)ray.side].width - 1);
		draw_column(&ray, i, texx, dsp);
		i++;
	}
	display(dsp);
}
