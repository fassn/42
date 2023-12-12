/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:13:31 by stsavida          #+#    #+#             */
/*   Updated: 2019/09/01 01:28:00 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			updates forward player movements
** @param env		main game structure
*/

void		move_forward(t_env *env)
{
	if (env->map[(int)(env->pos_y)][(int)(env->pos_x + env->dir_x *
			env->ws)] <= 0)
		env->pos_x += env->dir_x * env->ws;
	if (env->map[(int)(env->pos_y + env->dir_y * env->ws)]
			[(int)(env->pos_x)] <= 0)
		env->pos_y += env->dir_y * env->ws;
}

/*
** @desc			updates backward player movements
** @param env		main game structure
*/

void		move_backward(t_env *env)
{
	if (env->map[(int)(env->pos_y)][(int)(env->pos_x - env->dir_x *
			env->ws)] <= 0)
		env->pos_x -= env->dir_x * env->ws;
	if (env->map[(int)(env->pos_y - env->dir_y * env->ws)]
			[(int)(env->pos_x)] <= 0)
		env->pos_y -= env->dir_y * env->ws;
}

/*
** @desc			updates right strafe player movements
** @param env		main game structure
*/

void		move_right(t_env *env)
{
	if (env->map[(int)(env->pos_y)][(int)(env->pos_x - env->dir_y *
			env->ws)] <= 0)
		env->pos_x -= (env->dir_y) * env->ws;
	if (env->map[(int)(env->pos_y + env->dir_x * env->ws)]
			[(int)(env->pos_x)] <= 0)
		env->pos_y += (env->dir_x) * env->ws;
}

/*
** @desc			updates left strafe player movements
** @param env		main game structure
*/

void		move_left(t_env *env)
{
	if (env->map[(int)(env->pos_y)][(int)(env->pos_x + env->dir_y *
			env->ws)] <= 0)
		env->pos_x += (env->dir_y) * env->ws;
	if (env->map[(int)(env->pos_y - env->dir_x * env->ws)]
			[(int)(env->pos_x)] <= 0)
		env->pos_y -= (env->dir_x) * env->ws;
}

/*
** @desc			updates player vertical movements
** @param env		main game structure
*/

void	vertical_movement(t_env *env)
{
	if (env->fly == -1)
	{
		if (env->jump == 1 && env->pos_z < 0.8)
			env->pos_z += 0.1;
		if (env->key.up == 0 || env->pos_z >= 0.8)
			env->jump = 0;
		if (env->jump == 0 && env->pos_z > 0)
			env->pos_z -= 0.1;
		if (env->sneak == 1 && env->pos_z > -0.8)
			env->pos_z -= 0.1;
		if (env->key.down == 0)
			env->sneak = 0;
		if (env->sneak == 0 && env->pos_z < 0)
			env->pos_z += 0.1;
	}
	else
	{
		if (env->key.up == 1 && env->pos_z < 0.8)
			env->pos_z += 0.1;
		if (env->key.down == 1 && env->pos_z > -0.8)
			env->pos_z -= 0.1;
	}
}
