/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:21:43 by stsavida          #+#    #+#             */
/*   Updated: 2019/09/11 20:55:38 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			mouse movements events
** @param x, y		x, y screen pixel coordinates
** @param env		main game structure
*/

void	mouse_event_motion(int x, int y, t_env *env)
{
	float	tmp;
	
	if (env->gui == 0)
	{
		// horizontal rotation
		env->rs = 0.001 * env->m_delta_x;
		tmp = env->dir_x;
		env->dir_x = env->dir_x * cos(env->rs) - env->dir_y * sin(env->rs);
		env->dir_y = tmp * sin(env->rs) + env->dir_y * cos(env->rs);
		tmp = env->wll.plane_x;
		env->wll.plane_x = env->wll.plane_x * cos(env->rs) - env->wll.plane_y
			* sin(env->rs);
		env->wll.plane_y = tmp * sin(env->rs) + env->wll.plane_y * cos(env->rs);
		
		// vertical rotation
		env->rot -= env->m_delta_y / 5;
		if (env->rot < (W_HEIGHT / 2) * -1)
			env->rot = (W_HEIGHT / 2) * -1;
		if (env->rot > W_HEIGHT / 2)
			env->rot = W_HEIGHT / 2;
	}
	if (env->gui == 1)
	{
		if (((x >= 433 && x <= 594) && (y >= 437 && y <= 510)))
			env->btn[0] = 1;
		else
			env->btn[0] = 0;
		if (((x >= 433 && x <= 594) && (y >= 507 && y <= 605)))
			env->btn[1] = 1;
		else
			env->btn[1] = 0;
	}
}

/*
** @desc			mouse buttons pressed events
** @param button	mouse button
** @param env		main game structure
*/

void	mouse_event_pressed(SDL_MouseButtonEvent button, t_env *env)
{
	if (button.button == SDL_BUTTON_LEFT)
	{
		if (env->btn[0] == 1 && env->gui == 1)
			env->gui = 0;
		else if (env->btn[1] == 1 && env->gui == 1)
			exit_doom(env, "GoodBye :D", 0);
		else if (((env->pistol == 0) && button.x < W_WIDTH && button.y < W_HEIGHT) &&
		env->gui == 0 && env->hp > 0 && env->victory != 1)
		{
			if (env->ammo > 1)
			{
				if (Mix_PlayChannel(-1, env->gun_snd[0], 0) == -1)
					exit_doom(env, "Error: couldn't play gun_1.wav", 1);
				env->firing = 1;
				env->ammo--;
				env->pistol = 3;
			}
			if (Mix_PlayChannel(-1, env->gun_snd[1], 0) == -1)
					exit_doom(env, "Error: couldn't play gun_1.wav", 1);
		}
	}
}

/*
** @desc			mouse buttons released events
** @param button	mouse button
** @param env		main game structure
*/

void	mouse_event_released(SDL_MouseButtonEvent button, t_env *env)
{
	if (button.button == SDL_BUTTON_LEFT)
	{
		if ((button.x < W_WIDTH && button.y < W_HEIGHT) && env->gui == 0)
			env->firing = 0;
	}
}