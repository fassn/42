/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 19:19:36 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/22 19:39:07 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <math.h>

void			doors(t_env *env, float x, float y)
{
	if (fabs(env->dir_x) > fabs(env->dir_y))
	{
		if (env->map[(int)y][(int)(x + env->dir_x)] == HDOOR &&
				env->pos_z <= 1)
			env->map[(int)y][(int)(x + env->dir_x)] = HDOOR_O;
		else if (env->map[(int)y][(int)(x + env->dir_x)] == HDOOR_O &&
				env->map[(int)y][(int)x] != HDOOR_O && env->pos_z <= 1)
			env->map[(int)y][(int)(x + env->dir_x)] = HDOOR;
	}
	else if (fabs(env->dir_x) < fabs(env->dir_y))
	{
		if (env->map[(int)(y + env->dir_y)][(int)x] == VDOOR &&
				env->pos_z <= 1)
			env->map[(int)(y + env->dir_y)][(int)x] = VDOOR_O;
		else if (env->map[(int)(y + env->dir_y)][(int)x] == VDOOR_O &&
				env->map[(int)y][(int)x] != VDOOR_O && env->pos_z <= 1)
			env->map[(int)(y + env->dir_y)][(int)x] = VDOOR;
	}
}

static void		door_side_entry(t_env *env)
{
	if (
		env->map[env->map_y][env->map_x] < 9 &&
				env->wll.side == 0 && env->wll.rdx < 0 &&
				env->map[env->map_y][env->map_x + 1] == VDOOR_O)
		env->wll.tex_i = TEX_DOOR2;
	else if (
		env->map[env->map_y][env->map_x] < 9 &&
				env->wll.side == 0 && env->wll.rdx > 0 &&
				env->map[env->map_y][env->map_x - 1] == VDOOR_O &&
				(env->map[env->map_y][env->map_x - 2] <= 0 ||
				env->map[env->map_y][env->map_x - 2] >= 9))
		env->wll.tex_i = TEX_DOOR2;
	if (
		env->map[env->map_y][env->map_x] < 9 &&
				env->wll.side == 1 && env->wll.rdy < 0 &&
				env->map[env->map_y + 1][env->map_x] == HDOOR_O)
		env->wll.tex_i = TEX_DOOR2;
	else if (
		env->map[env->map_y][env->map_x] < 9 &&
				env->wll.side == 1 && env->wll.rdy > 0 &&
				env->map[env->map_y - 1][env->map_x] == HDOOR_O &&
				(env->map[env->map_y - 2][env->map_x] <= 0 ||
				env->map[env->map_y - 2][env->map_x] >= 9))
		env->wll.tex_i = TEX_DOOR2;
}

void			door_side(t_env *env)
{
	if (env->map[env->map_y][env->map_x] == VDOOR &&
			env->wll.side == 0)
		env->wll.tex_i = TEX_DOOR2;
	if (env->map[env->map_y][env->map_x] == HDOOR &&
			env->wll.side == 1)
		env->wll.tex_i = TEX_DOOR2;
	door_side_entry(env);
}
