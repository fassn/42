/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/24 02:18:42 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/27 22:21:26 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "../../inc/doomnukem.h"
#include <stdlib.h>

static int	parse_header(int fd, t_text *texture)
{
	char	*buffer;
	int		image_size;

	buffer = ft_memalloc(54);
	if (buffer == NULL)
		return (1);
	if (read(fd, buffer, 54) == 54)
	{
		if (buffer[0] != 'B' || buffer[1] != 'M')
		{
			free(buffer);
			return (1);
		}
		texture->offset = *(unsigned int *)&(buffer[10]);
		/* For some reason if I don't add 1 to ->w and ->h above, ->size is too small for the malloc call in parse_data() on Linux
		But then I get issues with the if (index != texture->size) check in parse_data() on Linux */ 
		// texture->w = *(int *)&(buffer[18]) + 1;
		// texture->h = *(int *)&(buffer[22]) + 1;
		texture->w = *(int *)&(buffer[18]);
		texture->h = *(int *)&(buffer[22]);
		image_size = *(int *)&(buffer[34]);
		if (texture->h < 0)
			texture->h *= -1;
		texture->bpp = buffer[28];
		texture->size = texture->w * texture->h * texture->bpp / 8;
		printf("texture->size %d image_size %d\n", texture->size, image_size);
		// texture->size = texture->w * texture->h;
	}
	free(buffer);
	if (texture->bpp != 24 || texture->h < 0 || texture->w < 0 ||
		texture->h > 4096 || texture->w > 4096)
		return (1);
	return (0);
}

static int	skip_header(int fd, t_text *texture)
{
	char	*skip;
	int		ret;

	if (texture->offset < 54)
		return (1);
	else if (texture->offset == 54)
		return (0);
	skip = ft_memalloc(texture->offset - 54);
	if (skip == NULL)
		return (1);
	ret = read(fd, skip, texture->offset - 54);
	free(skip);
	if (ret != (int)texture->offset - 54)
		return (1);
	return (0);
}

static int	parse_data(int fd, t_text *texture)
{
	int	index;
	int	line;

	texture->data = ft_memalloc(texture->size);
	if (texture->data == NULL)
		return (1);
	index = 0;
	line = texture->w * texture->bpp / 8;
	while (read(fd, texture->data + index, line) == line)
		index += line;
	if (index != texture->size)
	{
		printf("pute\n");
		free(texture->data);
		texture->data = NULL;
		return (1);
	}
	return (0);
}

static t_text	parse_bmp(char *filename)
{
	int			fd;
	static int	color = 0;
	t_text		texture;

	fd = open(filename, O_RDONLY);
	if (fd > 0)
	{
		if (parse_header(fd, &texture) == 0)
			if (skip_header(fd, &texture) == 0)
				if (parse_data(fd, &texture) == 0)
				{
					close(fd);
					return (texture);
				}
	}
	texture.h = 1;
	texture.w = 1;
	texture.data = ft_memalloc(3);
	texture.data[2] = color - 1;
	texture.data[1] = 127;
	texture.data[0] = color / 2;
	color += 64;
	close(fd);
	return (texture);
}

/*
** @desc			get the wall textures from files
** @param env		main game structure
*/

void				get_texture_wall(t_env *env)
{
	env->text_wll[TEX_WALL1] = parse_bmp("./texture/wall_1.bmp");
	env->text_wll[TEX_WALL2] = parse_bmp("./texture/wall_2.bmp");
	env->text_wll[TEX_WALL3] = parse_bmp("./texture/wall_3.bmp");
	env->text_wll[TEX_WALL4] = parse_bmp("./texture/wall_4.bmp");
	env->text_wll[TEX_CEIL] = parse_bmp("./texture/ceil.bmp");
	env->text_wll[TEX_FLOOR] = parse_bmp("./texture/floor.bmp");
	env->text_wll[TEX_GLASS] = parse_bmp("./texture/glass.bmp");
	env->text_wll[TEX_SKY] = parse_bmp("./texture/sky.bmp");
	env->text_wll[TEX_DOOR1] = parse_bmp("./texture/door1.bmp");
	env->text_wll[TEX_DOOR2] = parse_bmp("./texture/door2.bmp");
	env->text_wll[TEX_DECAL] = parse_bmp("./texture/doomface.bmp");
}

/*
** @desc			gets the gui textures from files
** @param env		main game structure
*/

void				get_texture_gui(t_env *env)
{
	env->text_gui[TEX_SHOTGUN1] = parse_bmp("./texture/shotgun.bmp");
	env->text_gui[TEX_SHOTGUN2] = parse_bmp("./texture/shotgun2.bmp");
	env->text_gui[TEX_SHOTGUN3] = parse_bmp("./texture/shotgun3.bmp");
	env->text_gui[TEX_SHOTGUN4] = parse_bmp("./texture/shotgun4.bmp");
	env->text_gui[TEX_SHOTGUN5] = parse_bmp("./texture/shotgun5.bmp");
	env->text_gui[TEX_SHOTGUN6] = parse_bmp("./texture/shotgun6.bmp");
	env->text_gui[TEX_SHOTGUN7] = parse_bmp("./texture/shotgun7.bmp");
	env->text_gui[TEX_SHOTGUN8] = parse_bmp("./texture/shotgun8.bmp");
	env->text_gui[TEX_SHOTGUN9] = parse_bmp("./texture/shotgun9.bmp");
	env->text_gui[TEX_BUTTONON] = parse_bmp("./texture/button_on.bmp");
	env->text_gui[TEX_BUTTONOFF] = parse_bmp("./texture/button_off.bmp");
	env->text_gui[TEX_CROSSHAIR] = parse_bmp("./texture/crosshair.bmp");
	env->text_gui[TEX_TITLE] = parse_bmp("./texture/title.bmp");
	env->text_gui[TEX_MENU] = parse_bmp("./texture/menu.bmp");
	env->text_gui[TEX_BACKGROUND] = parse_bmp("./texture/background.bmp");
	env->text_gui[TEX_BARFILLING] = parse_bmp("./texture/bar_filling.bmp");
	env->text_gui[TEX_BARAMMO] = parse_bmp("./texture/ammo_bar.bmp");
	env->text_gui[TEX_BARHP] = parse_bmp("./texture/life_bar.bmp");
	env->text_gui[TEX_TORCH] = parse_bmp("./texture/torch.bmp");
	env->text_gui[TEX_VICTORY] = parse_bmp("./texture/victory.bmp");
	env->text_gui[TEX_GAMEOVER] = parse_bmp("./texture/gameover.bmp");
	env->text_gui[TEX_KEY] = parse_bmp("./texture/key_gui.bmp");
}

/*
** @desc			gets the sprite textures from files
** @param env		main game structure
*/

void				get_texture_sprite(t_env *env)
{
	env->text_spr[TEX_BARREL] = parse_bmp("./texture/barrel.bmp");
	env->text_spr[TEX_MOBFRONT] = parse_bmp("./texture/mob-front.bmp");
	env->text_spr[TEX_MOBLEFT] = parse_bmp("./texture/mob-l-2.bmp");
	env->text_spr[TEX_MOBRIGHT] = parse_bmp("./texture/mob-r-2.bmp");
	env->text_spr[TEX_MOBBACK] = parse_bmp("./texture/mob-back.bmp");
	env->text_spr[TEX_MOBANIM1] = parse_bmp("./texture/mob_anim1.bmp");
	env->text_spr[TEX_MOBANIM2] = parse_bmp("./texture/mob_anim2.bmp");
	env->text_spr[TEX_MOBANIM3] = parse_bmp("./texture/mob_anim3.bmp");
	env->text_spr[TEX_MOBANIM4] = parse_bmp("./texture/mob_anim4.bmp");
	env->text_spr[TEX_MOBDEATH1] = parse_bmp("./texture/mob_death_anim1.bmp");
	env->text_spr[TEX_MOBDEATH2] = parse_bmp("./texture/mob_death_anim2.bmp");
	env->text_spr[TEX_MOBDEATH3] = parse_bmp("./texture/mob_death_anim3.bmp");
	env->text_spr[TEX_MOBDEATH4] = parse_bmp("./texture/mob_death_anim4.bmp");
	env->text_spr[TEX_MOBDEATH5] = parse_bmp("./texture/mob_death_anim5.bmp");
	env->text_spr[TEX_ITEMTORCH] = parse_bmp("./texture/item_torch.bmp");
	env->text_spr[TEX_ITEMAMMO] = parse_bmp("./texture/ammo.bmp");
	env->text_spr[TEX_ITEMKEY] = parse_bmp("./texture/key.bmp");
	env->text_spr[TEX_ITEMCHEST] = parse_bmp("./texture/chest.bmp");
	env->text_spr[TEX_IMPFRONT] = parse_bmp("./texture/imp-front.bmp");
	env->text_spr[TEX_IMPRIGHT] = parse_bmp("./texture/imp-right.bmp");
	env->text_spr[TEX_IMPLEFT] = parse_bmp("./texture/imp-left.bmp");
	env->text_spr[TEX_IMPBACK] = parse_bmp("./texture/imp-back.bmp");
}
