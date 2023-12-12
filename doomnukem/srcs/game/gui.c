/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/08 17:38:02 by stsavida          #+#    #+#             */
/*   Updated: 2019/09/11 15:50:51 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

static void				draw_mission_str(t_env *env)
{
	env->font = TTF_OpenFont("font/OpenSans-Regular.ttf", 10);
	if (env->font == NULL)
		ft_putstr("Error: Font didn't load properly\n");
	if (env->state == 1 && env->gui == 0 && env->n_gui_str < 8)
	{
		env->count_s++;
		if ((env->count_s % 60 == 0) && (env->count_s / 60) % 4 == 0)
			env->n_gui_str++;
	}
	if (env->n_gui_str == 0 && env->gui == 0)
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, T1, set_SDL_color(255, 255, 0, 255)));
	if (env->n_gui_str == 1 && env->gui == 0)
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, T2, set_SDL_color(255, 255, 0, 255)));
	if (env->n_gui_str == 2 && env->gui == 0)
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, T3, set_SDL_color(255, 255, 0, 255)));
	if (env->n_gui_str == 3 && env->gui == 0)
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, T4, set_SDL_color(255, 255, 0, 255)));
	if (env->n_gui_str == 4 && env->gui == 0)
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, T5, set_SDL_color(255, 255, 0, 255)));
	if (env->n_gui_str == 5 && env->gui == 0)
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, T6, set_SDL_color(255, 255, 0, 255)));
	if (env->n_gui_str == 6 && env->gui == 0)
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, T7, set_SDL_color(255, 255, 0, 255)));
	if (env->n_gui_str == 7 && env->gui == 0)
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, T8, set_SDL_color(255, 255, 0, 255)));
	TTF_CloseFont(env->font);
}

void					draw_main_menu_str(t_env *env)
{
	int 		i;

	i = -1;
	while (++i < 2)
	{
		if (env->btn[i] == 1)
			env->t_color[i] = set_SDL_color(255, 255, 0, 255);
		else
			env->t_color[i] = set_SDL_color(255, 255, 255, 255);
	}
	env->font = TTF_OpenFont("font/OpenSans-Regular.ttf", 10);
	if (env->font == NULL)
		ft_putstr("Error: Font didn't load properly\n");
	if (env->state == 0)
	{
		env->rect[0] = set_SDL_rect((W_WIDTH / 2) - 55, (W_HEIGHT / 2) + 88, 120, 40);
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, "START GAME", env->t_color[0]));
	}
	else
	{
		env->rect[0] = set_SDL_rect((W_WIDTH / 2) - 58, (W_HEIGHT / 2) + 88, 120, 40);
		env->text[0] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, "RESUME GAME", env->t_color[0]));
	}
	env->rect[1] = set_SDL_rect((W_WIDTH / 2) - 55, (W_HEIGHT / 2) + 183, 120, 40);
	env->text[1] = SDL_CreateTextureFromSurface(env->renderer, TTF_RenderUTF8_Solid(env->font, "EXIT GAME", env->t_color[1]));
	TTF_CloseFont(env->font);
}

static void				draw_main_menu(t_env *env)
{
	draw_image(env, env->text_gui[TEX_BACKGROUND], 0, 0);
	draw_image(env, env->text_gui[TEX_TITLE], (W_WIDTH / 2) - 434,
		(W_HEIGHT / 2) - 200);
	draw_image(env, env->text_gui[TEX_MENU], (W_WIDTH / 2) - 126,
		(W_HEIGHT / 2) + 50);
	if (env->btn[0] == 1)
		draw_image(env, env->text_gui[TEX_BUTTONON], (W_WIDTH / 2) - 81,
			(W_HEIGHT / 2) + 75);
	else
		draw_image(env, env->text_gui[TEX_BUTTONOFF], (W_WIDTH / 2) - 81,
			(W_HEIGHT / 2) + 75);
	if (env->btn[1] == 1)
		draw_image(env, env->text_gui[TEX_BUTTONON], (W_WIDTH / 2) - 81,
			(W_HEIGHT / 2) + 170);
	else
		draw_image(env, env->text_gui[TEX_BUTTONOFF], (W_WIDTH / 2) - 81,
			(W_HEIGHT / 2) + 170);
}

/*
** @desc			renders the GUI
** @param env		main game structure
*/

void					main_gui(t_env *env)
{
	if (env->gui == 0)
	{
		main_hud(env);
		if (env->hp > 0 && env->victory != 1)
			draw_mission_str(env);
	}
	else
	{
		draw_main_menu(env);
		draw_main_menu_str(env);
		SDL_SetRelativeMouseMode(SDL_FALSE);
	}
}
