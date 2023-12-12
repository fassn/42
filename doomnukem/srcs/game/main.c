/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/05 17:39:57 by stsavida          #+#    #+#             */
/*   Updated: 2019/09/11 20:57:40 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <unistd.h>

/*
** @desc			initializes the mlx framework and loads the textures
** @param env		main game structure
*/

static void				start_doom(t_env *env, int width, int height)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		exit_doom(env, "Error: SDL init error exiting...", 1);
	env->window = SDL_CreateWindow("doom-nukem", 0, 0, width, height, 0);
	if (env->window == NULL)
		exit_doom(env, "Error: window init error exiting...", 1);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	env->renderer = SDL_CreateRenderer(env->window, -1, 0);
	if (env->renderer == NULL)
		exit_doom(env, "Error: renderer init error exiting...", 1);
	env->texture = SDL_CreateTexture(env->renderer, SDL_PIXELFORMAT_RGB888,
		SDL_TEXTUREACCESS_STREAMING, width, height);
	if (env->texture == NULL)
		exit_doom(env, "Error: texture init error exiting...", 1);
	env->pixels = malloc((W_WIDTH * W_HEIGHT) * sizeof(int));
	if (TTF_Init() < 0)
		exit_doom(env, "Error: TTF init error exiting...", 1);
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		exit_doom(env, "Error: OpenAudio error exiting...", 1);
	// if (Mix_Init(MIX_INIT_OGG) < 0)
	// 	exit_doom(env, "Error: Mix init error exiting...", 1);
	if ((env->gun_snd[0] = Mix_LoadWAV(GUN_1)) == NULL)
		exit_doom(env, "Error: couldn't load gun_1.wav", 1);
	if ((env->gun_snd[1] = Mix_LoadWAV(GUN_2)) == NULL)
		exit_doom(env, "Error: couldn't load gun_2.wav", 1);
	if ((env->mus = Mix_LoadMUS(MUSIC)) == NULL)
		exit_doom(env, "Error: couldn't load music.ogg", 1);
}

/*
** @desc			gives info about key bindings to the player
*/

static	void			display_hook(void)
{
	ft_putstr("ESC = Quit\n");
	ft_putstr("UP/W = Move up          | DOWN/S = Move down\n");
	ft_putstr("LEFT/A = Move left      | RIGHT/D = Move right\n");
	ft_putstr("LEFT_CLICK = Shoot      | F = Fly mode\n");
	ft_putstr("SPACE = Jump            | E = Use door\n");
	ft_putstr("SHIFT = Sprint          | CTRL = Crouch\n");
	ft_putstr("G = Posters             | R = Reload\n");
}

/*
** @desc			main entry point to the program
** @param argv		*.dn map file to be specified at launch
** @return int		0 at program exit
*/

int						main(int argc, char **argv)
{
	t_env	*env;

	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		exit(1);
	init_struct_core(env);
	if (argc != 2)
		exit_doom(env, "usage: doom-nukem source_file.dn", 1);
	ft_check_file(env, argv[1]);
	if (access(env->file, F_OK) != -1)
		ft_import(env, env->file, 0);
	else
		exit_doom(env, "Unable to load file.", 0);
	check_texture_str(env);
	display_hook();
	start_doom(env, W_WIDTH, W_HEIGHT);
	env->gl.prevclock = clock();
	while (1)
		redraw(env);
	return (0);
}
