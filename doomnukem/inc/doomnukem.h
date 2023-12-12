/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doomnukem.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:31:47 by stsavida          #+#    #+#             */
/*   Updated: 2019/09/11 20:49:42 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOMNUKEM_H
# define DOOMNUKEM_H

# define W_WIDTH		1024
# define W_HEIGHT		720
# define KEYPRESS		2
# define KEYRELEASE		3
# define CLOSE			17
# define NB_THREADS		8

# define T1 			"      WELCOME BACK, AGENT SERGUEI      "
# define T2 			" ONE OF OUR ANCIENT SOLDIER LOST A KEY "
# define T3 			"WHO ALLOWED TO OPEN A CHEST CONTAINING "
# define T4 			"     THE PLAN OF A LEGENDARY WEAPON    "
# define T5 			" YOU KNOW THIS MAZE BETTER THAN ANYONE "
# define T6 			"          YOU MUST FIND THIS KEY       "
# define T7 			" KILL ALL THOSE WHO WILL BE ON YOU WAY "
# define T8 			"            GOD BLESS YOU              "

# define MUSIC			"snd/music.ogg"
# define GUN_1			"snd/gun_1.wav"
# define GUN_2			"snd/gun_2.wav"

# include "textures.h"
# include "key_bindings.h"
# include "../libs/libft/libft.h"
// # include "../libs/minilibx/mlx.h"
# include "./game/xpm_parser_struct.h"
# include <SDL2/SDL.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_mixer.h>
# include <stdlib.h>
# include <time.h>

typedef struct		s_gameloop
{
	clock_t			prevclock;
	clock_t			currclock;
	clock_t			frameclock;
}					t_gameloop;

typedef struct		s_key
{
	int				up;
	int				down;
}					t_key;

typedef struct		s_wall_cast
{
	float			sdx;
	float			sdy;
	float			ddx;
	float			ddy;
	int				step_x;
	int				step_y;
	float			plane_x;
	float			plane_y;
	int				tex_x;
	int				tex_y;
	float			wall_x;
	float			rdx;
	float			rdy;
	int				side;
	float			pwd;
	int				drawstart;
	int				drawend;
	int				lineheight;
	float			fog;
	int				tex_i;
	int				decal;
}					t_wall_cast;

typedef struct		s_floor_cast
{
	float			x;
	float			y;
	float			weight;
	float			curr_x;
	float			curr_y;
	int				tex_x;
	int				tex_y;
	float			dist_wall;
	float			dist_player;
	float			current_dist;
}					t_floor_cast;

typedef struct		s_sprite
{
	float			x;
	float			y;
	int				text;
	int				type;
	int				hp;
	int				multi;
	int				anim;
	int				death_anim;
	int				picked;
}					t_sprite;

typedef struct		s_sprite_cast
{
	float			zbuffer[W_WIDTH];
	int				order[1024];
	float			dist[1024];
	t_sprite		data[1024];
	int				nb_sprite;
	float			x;
	float			y;
	float			inv_det;
	float			trans_x;
	float			trans_y;
	int				scr_x;
	int				h;
	int				w;
	int				dsx;
	int				dsy;
	int				dex;
	int				dey;
	int				tex_x;
	int				tex_y;
	int				stripe;
	float			dx;
	float			dy;
	float			angle;
}					t_sprite_cast;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
}					t_color;

typedef struct		s_env
{
	SDL_Renderer	*renderer;
	SDL_Window		*window;
	SDL_Texture		*texture;
	TTF_Font		*font;
	SDL_Texture		*text[2];
	SDL_Rect		rect[2];
	SDL_Color 		t_color[2];
	Mix_Chunk		*gun_snd[2];
	Mix_Music		*mus;
	t_gameloop		gl;
	t_text			text_wll[NB_TEX_WLL];
	t_text			text_gui[NB_TEX_GUI];
	t_text			text_spr[NB_TEX_SPR];
	t_wall_cast		wll;
	t_floor_cast	flr;
	t_sprite_cast	spr;
	t_key			key;
	t_color			color;
	int				map[34][34];
	struct s_env	*core;
	int				sky_mode;
	char			*file;
	int				spawn_placed;
	int				fd;
	int				*pixels;
	int				bpp;
	int				pitch;
	int				size_line;
	int				endian;
	float			dir_x;
	float			dir_y;
	float			pos_x;
	float			pos_y;
	float			pos_z;
	float			ws;
	float			rs;
	float			cam_x;
	int				map_x;
	int				map_y;
	int				pistol;
	int				firing;
	int				ammo;
	int				mute;
	float			rot;
	int				nt;
	int				jump;
	int				sneak;
	int				fly;
	int				skyx;
	int				skyy;
	float			hp;
	int				btn[2];
	int				state;
	int				gui;
	int				torch;
	int				item_key;
	int				victory;
	int				count_s;
	int				n_gui_str;
	int				m_delta_x;
	int				m_delta_y;
}					t_env;

/*
** struct.c
*/
void				init_struct_core(t_env *env);

/*
** parser.c
*/
void				ft_import(t_env *env, char *path, int y);
void				ft_check_file(t_env *env, char *path);

/*
** load_texture.c
*/
void				check_texture_str(t_env *env);

/*
** get_texture.c
*/
void				get_texture_wall(t_env *env);
void				get_texture_gui(t_env *env);
void				get_texture_sprite(t_env *env);

/*
** render.c
*/
void				get_clock_time(t_env *env);
void				redraw(t_env *env);
void				pixel_put(t_env *env, int x, int y, t_color color);
void				render(t_env *env);

/*
** raycast.c
*/
void				*thread_core(void *arg);

/*
** draw_wall.c
*/
void				draw_wall(t_env *env, int x, int text);

/*
** draw_floor_ceiling.c
*/
void				draw_floor_or_ceiling(t_env *env, int x, int side,
	t_text *text);

/*
** draw_gui.c
*/
void				draw_image(t_env *env, t_text text, int xp, int yp);
void				draw_weapon(t_env *env, t_text *text, int pos_x, int pos_y);
void				draw_gui(t_env *env);

/*
** draw_sprite.c
*/
void				draw_sprite(t_env *env);
void				sort_sprite(t_env *env, int i);
void				*thread_sprite(void *arg);

/*
** draw.sprite2.c
*/
int					get_texture(t_env *env);
void				pixel_put_sprites(t_env *env, int color, int y, int s);

/*
** init_sprite.c
*/
void				create_sprites(t_sprite *spr, float x, float y, int value);
void				init_sprites(t_env *env, int x, int y, int *i);

/*
** data.c
*/
void				exit_doom(t_env *env, char *str, int e);

/*
** utils.c
*/
void				comb_sort(int *order, float *dist, int amount);
SDL_Color			set_SDL_color(int r, int g, int b, int a);
SDL_Rect			set_SDL_rect(int x, int y, int w, int h);

/*
** move.c
*/
void				move_forward(t_env *env);
void				move_backward(t_env *env);
void				move_right(t_env *env);
void				move_left(t_env *env);
void				vertical_movement(t_env *env);

/*
** keyboard_hook.c
*/
void				keyboard_event_pressed(SDL_KeyboardEvent key, t_env *env);
void				keyboard_event_released(SDL_KeyboardEvent key, t_env *env);
void				keyboard_state(t_env *env, const unsigned char *state);

/*
** mouse_hook.c
*/
void				mouse_event_motion(int x, int y, t_env *env);
void				mouse_event_pressed(SDL_MouseButtonEvent button, t_env *env);
void				mouse_event_released(SDL_MouseButtonEvent button, t_env *env);

/*
** color.c
*/
void				get_rgb_color(t_env *env, int color);
void				get_wall_fog(t_env *env, int color);
void				get_floor_or_ceiling_fog(t_env *env, int color, int y);
void				get_sprite_fog(t_env *env, int color, float dist);
void				get_rgb_color(t_env *env, int color);

/*
** enemy.c
*/
void				enemy_core(t_env *env, t_sprite *enemy, int s, int i);

/*
** object.c
*/
void				object_core(t_env *env, t_sprite *enemy, int i);

/*
** gui.c
*/
void				main_gui(t_env *env);
void				draw_main_menu_str(t_env *env);

/*
** hud.c
*/
void				main_hud(t_env *env);

/*
** door.c
*/
void				doors(t_env *env, float x, float y);
void				door_side(t_env *env);

/*
** decal.c
*/
void				decal(t_env *env);

/*
** loader_xpm.c
*/
t_text				load_xpm(t_env *env, const char *name);

/*
** loader_utils.c
*/
t_color_p			get_color(t_env *env, char *line, t_parser *p);
unsigned int		rvb_to_ui(t_env *env, char *src);
int					ft_atoi_base2(char *src, int base);

#endif
