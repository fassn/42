/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_xpm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 21:54:06 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/31 12:46:51 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"
#include <fcntl.h>
#include <unistd.h>

static char		*get_raw(t_env *env, t_parser *p)
{
	char	*raw;
	char	*line;
	int		ret;

	line = NULL;
	ret = 0;
	while ((get_next_line(p->fd, &line) <= 0))
	{
		return (ft_memalloc(p->raw_len));
	}
	if (line[0] == '"')
		p->ret += p->texture.w * p->info.y;
	raw = get_raw(env, p);
	if (raw == NULL)
		exit_doom(env, "Error XPM : malloc failed.", 1);
	if (line != NULL)
	{
		if (line[0] == '"')
		{
			if (p->raw_len != 0)
				ft_strncpy(raw + (p->raw_len - p->texture.w * p->info.y), line + 1, p->texture.w * p->info.y);
			p->raw_len -= p->texture.w * p->info.y;
		}
	}
	free(line);
	return(raw);
}

static void		create_texture(t_env *env, t_parser *p)
{
	int		i;
	int		c;

	p->raw_len = p->texture.w * p->texture.h * p->info.y;
	p->raw = get_raw(env, p);
	if (!(p->texture.str = (unsigned int*)malloc(sizeof(unsigned int) \
				* p->texture.w * p->texture.h)))
		exit_doom(env, "Error XPM : malloc failed.", 1);
	p->line = ft_memalloc(p->info.y);
	i = -1;
	while (++i < p->texture.w * p->texture.h)
	{
		c = 0;
		ft_strncpy(p->line, p->raw + (i * p->info.y), p->info.y);
		while (c < p->info.x && !(ft_strequ(p->color[c].id, p->line)))
			c++;
		if (c >= p->info.x && p->raw[i * p->info.y] != '"')
			exit_doom(env, "Error XPM : color not found.", 1);
		else
			((int*)(p->texture.str))[i] = p->color[c].value;
		ft_bzero(p->line, p->info.y + 1);
	}
	free(p->line);
	free(p->raw);
}

static void		parse_texture(t_env *env, t_parser *p)
{
	p->color = NULL;
	if (!(p->color = (t_color_p*)malloc(sizeof(t_color_p) * p->info.x)))
		exit_doom(env, "Error XPM : malloc failed.", 1);
	p->i = 0;
	p->line = NULL;
	while (p->i < p->info.x)
	{
		if ((p->ret = get_next_line(p->fd, &p->line)) < 0)
			exit_doom(env, "Error XPM : invalid file.", 0);
		if (p->line[0] == '"')
		{
			p->color[p->i] = get_color(env, p->line, p);
			(p->i)++;
		}
		free(p->line);
	}
	p->ret = 0;
	p->line = NULL;
	create_texture(env, p);
	free(p->color);
}

static void		get_info(t_env *env, t_parser *p)
{
	p->line = NULL;
	p->ret = 1;
	while (!(ft_strchr(p->line, '"')) && p->ret > 0)
	{
		if ((p->ret = get_next_line(p->fd, &p->line)) < 0)
			exit_doom(env, "Error : seems like we can't access the file.", 0);
	}
	if (p->ret == 0 && !(ft_strchr(p->line, '"')))
		exit_doom(env, "Error XPM : no header found.", 0);
	if (!(p->tabtmp = ft_strsplit(p->line + 1, ' ')))
		exit_doom(env, "Error XPM : malloc failed.", 1);
	free(p->line);
	p->texture.w = ft_atoi(p->tabtmp[0]);
	p->texture.h = ft_atoi(p->tabtmp[1]);
	p->info = (t_pixel){ft_atoi(p->tabtmp[2]), ft_atoi(p->tabtmp[3])};
	p->ret = 0;
	while (p->ret < 5)
		free(p->tabtmp[(p->ret)++]);
	free(p->tabtmp);
}

t_text			load_xpm(t_env *env, const char *name)
{
	t_parser	p;

	p.path = NULL;
	if (!(p.path = ft_strjoin("texture/", name)))
		exit_doom(env, "Error XPM : malloc failed.", 1);
	if (!(p.fd = open(p.path, O_RDONLY)) || access(p.path, F_OK) == -1)
		exit_doom(env, "Error XPM : can't open file.", 1);
	ft_putendl(p.path);
	free(p.path);
	p.texture.str = NULL;
	get_info(env, &p);
	parse_texture(env, &p);
	if ((close(p.fd)) == -1)
		exit_doom(env, "Error XPM : can't close file.", 1);
	return (p.texture);
}
