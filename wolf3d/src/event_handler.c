/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 11:42:11 by phaydont          #+#    #+#             */
/*   Updated: 2019/08/24 02:34:19 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void	keyboard_state(t_display *dsp, const unsigned char *state)
{
	if (state[SDL_SCANCODE_LEFT])
		rotation(dsp, -2);
	if (state[SDL_SCANCODE_RIGHT])
		rotation(dsp, 2);
	if (state[SDL_SCANCODE_UP])
		move(dsp, 1);
	if (state[SDL_SCANCODE_DOWN])
		move(dsp, -1);
	if (state[SDL_SCANCODE_A])
		translate(dsp, 1);
	if (state[SDL_SCANCODE_D])
		translate(dsp, -1);
}

static void	keyboard_event(SDL_KeyboardEvent key, t_display *dsp)
{
	if (key.keysym.sym == SDLK_ESCAPE)
		dsp->exit = 1;
}

void		event_loop(t_display *dsp)
{
	SDL_Event			event;
	const unsigned char	*state;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
			keyboard_event(event.key, dsp);
		else if (event.type == SDL_DROPFILE)
		{
			SDL_free(event.drop.file);
			return ;
		}
		else if (event.type == SDL_QUIT)
		{
			dsp->exit = 1;
			return ;
		}
	}
	state = SDL_GetKeyboardState(NULL);
	keyboard_state(dsp, state);
	raycast(dsp);
}
