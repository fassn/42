/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keyboard.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 19:28:18 by cfargere          #+#    #+#             */
/*   Updated: 2019/09/01 01:31:16 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			hooks for the keyboard press
** @param key		keyboard key pressed
** @param env		main game structure
*/

void	keyboard_event_pressed(SDL_KeyboardEvent key, t_env *env)
{
	if (key.keysym.scancode == SDL_SCANCODE_LCTRL && env->pos_z >= -0.8 &&
		env->key.down == 0)
	{
		env->key.down = 1;
		env->sneak = 1;
		env->ws = 0.04;
	}
	if (key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		env->ws = 0.4;
	if (key.keysym.scancode == SDL_SCANCODE_SPACE && env->key.up == 0 && env->pos_z <= 0.8) 
	{
		env->key.up = 1;
		env->jump = 1;
	}
	if (key.keysym.scancode == SDL_SCANCODE_E)
		doors(env, env->pos_x, env->pos_y);
	if (key.keysym.scancode == SDL_SCANCODE_F)
		env->fly *= -1;
	if (key.keysym.scancode == SDL_SCANCODE_G)
		env->wll.decal = env->wll.decal == 0 ? 1 : 0;
	if (key.keysym.scancode == SDL_SCANCODE_R)
		env->ammo = 2;
	if (key.keysym.scancode == SDL_SCANCODE_ESCAPE && env->gui == 0)
	{
		env->gui = 1;
		env->btn[0] = 0;
		env->btn[1] = 0;
	}
	else if (key.keysym.scancode == SDL_SCANCODE_ESCAPE && env->gui == 1)
		exit_doom(env, "GoodBye :D", 0);
}

/*
** @desc			hooks for the keyboard release
** @param key		keyboard key pressed
** @param env		main game structure
*/

void	keyboard_event_released(SDL_KeyboardEvent key, t_env *env)
{
	if (key.keysym.scancode == SDL_SCANCODE_LCTRL)
	{
		env->key.down = 0;
		env->ws = 0.06;
	}
	if (key.keysym.scancode == SDL_SCANCODE_LSHIFT)
		env->ws = 0.06;
	if (key.keysym.scancode == SDL_SCANCODE_SPACE)
	{
		env->key.up = 0;
	}
}

/*
** @desc			hooks for the keyboard states
** @param env		main game structure
** @param state		state of the key pressed
*/

void	keyboard_state(t_env *env, const unsigned char *state)
{
	if (state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A])
		move_left(env);
	if (state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D])
		move_right(env);
	if (state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W])
		move_forward(env);
	if (state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S])
		move_backward(env);
	if (state[SDL_SCANCODE_KP_PLUS] && env->rot < (W_HEIGHT / 2) - 20)
		env->rot += 20;
	if (state[SDL_SCANCODE_KP_MINUS] && env->rot > ((W_HEIGHT / 2) - 20) * -1)
		env->rot -= 20;
	vertical_movement(env);
}
