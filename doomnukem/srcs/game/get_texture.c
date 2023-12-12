/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 19:05:04 by stsavida          #+#    #+#             */
/*   Updated: 2019/08/23 16:43:22 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

/*
** @desc			get the wall textures from files
** @param env		main game structure
*/

void				get_texture_wall(t_env *env)
{
	env->text_wll[TEX_WALL1] = load_xpm(env, "wall_1.xpm");
	env->text_wll[TEX_WALL2] = load_xpm(env, "wall_2.xpm");
	env->text_wll[TEX_WALL3] = load_xpm(env, "wall_3.xpm");
	env->text_wll[TEX_WALL4] = load_xpm(env, "wall_4.xpm");
	env->text_wll[TEX_CEIL] = load_xpm(env, "ceil.xpm");
	env->text_wll[TEX_FLOOR] = load_xpm(env, "floor.xpm");
	env->text_wll[TEX_GLASS] = load_xpm(env, "glass.xpm");
	env->text_wll[TEX_SKY] = load_xpm(env, "sky.xpm");
	env->text_wll[TEX_DOOR1] = load_xpm(env, "door1.xpm");
	env->text_wll[TEX_DOOR2] = load_xpm(env, "door2.xpm");
	env->text_wll[TEX_DECAL] = load_xpm(env, "doomface.xpm");
}

/*
** @desc			gets the gui textures from files
** @param env		main game structure
*/

void				get_texture_gui(t_env *env)
{
	env->text_gui[TEX_SHOTGUN1] = load_xpm(env, "shotgun.xpm");
	env->text_gui[TEX_SHOTGUN2] = load_xpm(env, "shotgun2.xpm");
	env->text_gui[TEX_SHOTGUN3] = load_xpm(env, "shotgun3.xpm");
	env->text_gui[TEX_SHOTGUN4] = load_xpm(env, "shotgun4.xpm");
	env->text_gui[TEX_SHOTGUN5] = load_xpm(env, "shotgun5.xpm");
	env->text_gui[TEX_SHOTGUN6] = load_xpm(env, "shotgun6.xpm");
	env->text_gui[TEX_SHOTGUN7] = load_xpm(env, "shotgun7.xpm");
	env->text_gui[TEX_SHOTGUN8] = load_xpm(env, "shotgun8.xpm");
	env->text_gui[TEX_SHOTGUN9] = load_xpm(env, "shotgun9.xpm");
	env->text_gui[TEX_BUTTONON] = load_xpm(env, "button_on.xpm");
	env->text_gui[TEX_BUTTONOFF] = load_xpm(env, "button_off.xpm");
	env->text_gui[TEX_CROSSHAIR] = load_xpm(env, "crosshair.xpm");
	env->text_gui[TEX_TITLE] = load_xpm(env, "title.xpm");
	env->text_gui[TEX_MENU] = load_xpm(env, "menu.xpm");
	env->text_gui[TEX_BACKGROUND] = load_xpm(env, "background.xpm");
	env->text_gui[TEX_BARFILLING] = load_xpm(env, "bar_filling.xpm");
	env->text_gui[TEX_BARAMMO] = load_xpm(env, "ammo_bar.xpm");
	env->text_gui[TEX_BARHP] = load_xpm(env, "life_bar.xpm");
	env->text_gui[TEX_TORCH] = load_xpm(env, "torch.xpm");
	env->text_gui[TEX_VICTORY] = load_xpm(env, "victory.xpm");
	env->text_gui[TEX_GAMEOVER] = load_xpm(env, "gameover.xpm");
	env->text_gui[TEX_KEY] = load_xpm(env, "key_gui.xpm");
}

/*
** @desc			gets the sprite textures from files
** @param env		main game structure
*/

void				get_texture_sprite(t_env *env)
{
	env->text_spr[TEX_BARREL] = load_xpm(env, "barrel.xpm");
	env->text_spr[TEX_MOBFRONT] = load_xpm(env, "mob-front.xpm");
	env->text_spr[TEX_MOBLEFT] = load_xpm(env, "mob-l-2.xpm");
	env->text_spr[TEX_MOBRIGHT] = load_xpm(env, "mob-r-2.xpm");
	env->text_spr[TEX_MOBBACK] = load_xpm(env, "mob-back.xpm");
	env->text_spr[TEX_MOBANIM1] = load_xpm(env, "mob_anim1.xpm");
	env->text_spr[TEX_MOBANIM2] = load_xpm(env, "mob_anim2.xpm");
	env->text_spr[TEX_MOBANIM3] = load_xpm(env, "mob_anim3.xpm");
	env->text_spr[TEX_MOBANIM4] = load_xpm(env, "mob_anim4.xpm");
	env->text_spr[TEX_MOBDEATH1] = load_xpm(env, "mob_death_anim1.xpm");
	env->text_spr[TEX_MOBDEATH2] = load_xpm(env, "mob_death_anim2.xpm");
	env->text_spr[TEX_MOBDEATH3] = load_xpm(env, "mob_death_anim3.xpm");
	env->text_spr[TEX_MOBDEATH4] = load_xpm(env, "mob_death_anim4.xpm");
	env->text_spr[TEX_MOBDEATH5] = load_xpm(env, "mob_death_anim5.xpm");
	env->text_spr[TEX_ITEMTORCH] = load_xpm(env, "item_torch.xpm");
	env->text_spr[TEX_ITEMAMMO] = load_xpm(env, "ammo.xpm");
	env->text_spr[TEX_ITEMKEY] = load_xpm(env, "key.xpm");
	env->text_spr[TEX_ITEMCHEST] = load_xpm(env, "chest.xpm");
	env->text_spr[TEX_IMPFRONT] = load_xpm(env, "imp-front.xpm");
	env->text_spr[TEX_IMPRIGHT] = load_xpm(env, "imp-right.xpm");
	env->text_spr[TEX_IMPLEFT] = load_xpm(env, "imp-left.xpm");
	env->text_spr[TEX_IMPBACK] = load_xpm(env, "imp-back.xpm");
}
