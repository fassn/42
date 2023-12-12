/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 03:35:01 by cfargere          #+#    #+#             */
/*   Updated: 2019/09/11 20:53:27 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include <time.h>

/*
** @desc			gets clock time after gamestate has been refreshed
** @param env		main game structure
*/

void				get_clock_time(t_env *env)
{
	env->gl.currclock = clock();
	env->gl.frameclock = env->gl.currclock - env->gl.prevclock;
	if (env->gl.frameclock < CLOCKS_PER_SEC)
		sleep((float)(CLOCKS_PER_SEC - env->gl.frameclock) /
				CLOCKS_PER_SEC / 10.0);
	env->gl.prevclock = env->gl.currclock;
}

/*
** @desc			checks the SDL events (keyboard and mouse)
** @param env		main game structure
*/

static void			check_SDL_event(t_env *env)
{
	SDL_Event			event;
	const unsigned char	*state;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
			keyboard_event_pressed(event.key, env);
		else if (event.type == SDL_KEYUP)
			keyboard_event_released(event.key, env);
		else if (event.type == SDL_MOUSEBUTTONDOWN)
			mouse_event_pressed(event.button, env);
		else if (event.type == SDL_MOUSEBUTTONUP)
			mouse_event_released(event.button, env);
		else if (event.type == SDL_MOUSEMOTION)
		{
			env->m_delta_x = event.motion.xrel;
			env->m_delta_y = event.motion.yrel;
			mouse_event_motion(event.motion.x, event.motion.y, env);
		}
		else if (event.type == SDL_DROPFILE)
		{
			SDL_free(event.drop.file);
			return ;
		}
		else if (event.type == SDL_QUIT)
			exit_doom(env, "Red cross has been clicked on", 1);
	}
	state = SDL_GetKeyboardState(NULL);
	keyboard_state(env, state);
}

/*
** @desc			refreshes the gamestate (called in loop)
** @param env		main game structure
*/

void				redraw(t_env *env)
{
	int		i;

	check_SDL_event(env);
	i = 0;
	while (i < W_WIDTH * W_HEIGHT)
		env->pixels[i++] = 0;
	if (env->gui == 0 && env->hp > 0 && env->victory != 1)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		if (env->state == 0)
		{
			if (Mix_PlayMusic(env->mus, 0))
				exit_doom(env, "Error: music couldn't be played", 1);
		}
		env->state = 1;
		
		render(env);
		draw_sprite(env);
	}
	main_gui(env);
	SDL_RenderClear(env->renderer);
	SDL_UpdateTexture(env->texture, NULL, env->pixels, env->pitch);
	SDL_RenderCopy(env->renderer, env->texture, NULL, NULL);
	if (env->gui == 1)
	{
		SDL_RenderCopy(env->renderer, env->text[0], NULL, &env->rect[0]);
		SDL_RenderCopy(env->renderer, env->text[1], NULL, &env->rect[1]);
	}
	else
		env->rect[0] = set_SDL_rect((W_WIDTH / 2) - 170, (W_HEIGHT / 2) - 350, 600, 50);
		SDL_RenderCopy(env->renderer, env->text[0], NULL, &env->rect[0]);
	SDL_RenderPresent(env->renderer);

	get_clock_time(env);
}

/*
** @desc			puts pixel onto the screen buffer
** @param env		main game structure
** @param x, y		screen pixel coordinates
** @param color		rgb color to write onto the screen buffer
*/

void				pixel_put(t_env *env, int x, int y, t_color color)
{
	if (x >= W_WIDTH || y >= W_HEIGHT || x < 0 || y < 0)
		return ;
	env->pixels[y * W_WIDTH + x] = color.r * 65536 + color.g * 256 + color.b;
	// env->pixels[y * W_WIDTH + x] = color.r;
	// env->pixels[y * W_WIDTH + x + 1] = color.g;
	// env->pixels[y * W_WIDTH + x + 2] = color.b;
	// env->pixels[((env->bpp / 8) * x) + (env->size_line * y)
	// 	+ 0] = color.b;
	// env->pixels[((env->bpp / 8) * x) + (env->size_line * y)
	// 	+ 1] = color.g;
	// env->pixels[((env->bpp / 8) * x) + (env->size_line * y)
	// 	+ 2] = color.r;
}

/*
** @desc			main rendering function
** @param env		main game structure
*/

void				render(t_env *env)
{
	pthread_t		thread[8];
	t_env			*env_t;

	env_t = malloc(sizeof(t_env) * 9);
	env->nt = 0;
	while (env->nt < NB_THREADS)
	{
		ft_memcpy((void*)&env_t[env->nt], (void*)env, sizeof(t_env));
		env_t[env->nt].core = env;
		pthread_create(&thread[env->nt], NULL, thread_core,
			&env_t[env->nt]);
		env->nt++;
	}
	while (env->nt--)
		pthread_join(thread[env->nt], NULL);
	free(env_t);
}
