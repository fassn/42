/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:42:26 by stsavida          #+#    #+#             */
/*   Updated: 2019/09/10 19:30:13 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			3rd part of game structure initialization
** @param env		main game structure
*/

static void				init_move_var(t_env *env)
{
	env->key.up = 0;
	env->key.down = 0;
	env->jump = 0;
	env->sneak = 0;
	env->fly = -1;
}

/*
** @desc			2nd part of game structure initialization
** @param env		main game structure
*/

static void				init_struct_core2(t_env *env)
{
	env->ws = 0.06;
	env->rs = 0.2;
	env->pistol = 0;
	env->firing = 0;
	env->ammo = 2;
	env->torch = -1;
	env->item_key = 0;
	env->mute = -1;
	env->spr.nb_sprite = 0;
	env->rot = 0;
	env->gui = 1;
	env->text[0] = NULL;
	env->text[1] = NULL;
	env->state = 0;
	env->victory = 0;
	env->wll.decal = 0;
	env->count_s = 0;
	env->n_gui_str = 0;
	init_move_var(env);
}

/*
** @desc			initializes main game structure variables
** @param env		main game structure
*/

void					init_struct_core(t_env *env)
{
	int x;
	int y;

	env->pitch = sizeof(int) * W_WIDTH;
	env->spawn_placed = 0;
	y = -1;
	while (++y < 32 + 2)
	{
		x = -1;
		while (++x < 32 + 2)
			env->map[y][x] = 1;
	}
	env->pos_x = -1;
	env->pos_y = -1;
	env->pos_z = 0;
	env->dir_x = 1;
	env->dir_y = 0;
	env->wll.plane_x = 0;
	env->wll.plane_y = 0.66;
	env->btn[0] = 0;
	env->btn[1] = 0;
	init_struct_core2(env);
}
