/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/30 18:43:32 by stsavida          #+#    #+#             */
/*   Updated: 2019/09/11 20:55:50 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <unistd.h>

/*
** @desc			destroys the textures/SDL buffers
** @param env		main game structure
*/

static void				clear_buffers(t_env *env)
{
	int y;

	y = 0;
	while (y < 11 && env->text_wll[y].str != NULL)
		free(env->text_wll[y++].str);
	y = 0;
	while (y < 22 && env->text_gui[y].str != NULL)
		free(env->text_gui[y++].str);
	y = 0;
	while (y < 22 && env->text_spr[y].str != NULL)
		free(env->text_spr[y++].str);
	free(env->pixels);
}

/*
** @desc			frees memory at program exit
** @param env		main game structure
** @param str		message to be displayed on exit
** @param e			error signal number
*/

void					exit_doom(t_env *env, char *str, int e)
{
	ft_putendl_fd(str, e + 1);
	if (env->fd == -1)
		close(env->fd);
	clear_buffers(env);
	if (env->renderer)
		SDL_DestroyRenderer(env->renderer);
	if (env->window)
		SDL_DestroyWindow(env->window);
	if (env->texture)
		SDL_DestroyTexture(env->texture);
	SDL_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	free(env);
	exit(e);
}
