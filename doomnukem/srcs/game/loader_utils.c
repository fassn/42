/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loader_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 21:54:04 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/31 12:47:23 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/doomnukem.h"

int				rec_atoi_base(char *src, int base, char *tab)
{
	int	len;
	int	i;

	if (!src[0] || !(ft_strchr(tab, src[0])))
		return (0);
	len = (int)ft_strlen(src);
	i = 0;
	while (tab[i] && tab[i] != src[0] && i < base)
		i++;
	return (i * ft_pow(base, len - 1) + rec_atoi_base(src + 1, base, tab));
}

int				ft_atoi_base2(char *src, int base)
{
	int			value;
	size_t		i;

	if (!src || base < 2 || base > 16)
		return (0);
	i = -1;
	while (++i < ft_strlen(src))
		src[i] = ft_toupper(src[i]);
	value = rec_atoi_base(src, base, "0123456789ABCDEF");
	return (value);
}

unsigned int	rvb_to_ui(t_env *env, char *src)
{
	int		value;
	char	name[7];

	(void)env;
	ft_bzero(name, 7);
	if (!src || ft_strlen(src) < 2)
		return (0);
	ft_strncpy(name, src, ft_strlen(src) - 2);
	value = ft_atoi_base2(name, 16);
	return (value);
}

t_color_p		get_color(t_env *env, char *line, t_parser *p)
{
	t_color_p	color;
	char		tmp[12];
	int			i;

	ft_bzero(color.id, 3);
	ft_strncpy(color.id, line + 1, p->info.y);
	i = 0;
	while (line[i] && line[i] != 'c')
		i++;
	i++;
	while (line[i] && line[i] != '#' && line[i] != 'n' \
			&& line[i] != 'N')
		i++;
	i += (line[i] == 'n' || line[i] == 'N' ? 0 : 1);
	ft_strncpy(tmp, line + i, 12);
	if (ft_strnequ(tmp, "none", 4) || ft_strnequ(tmp, "None", 4))
		color.value = 0x000000;
	else
		color.value = rvb_to_ui(env, tmp);
	return (color);
}
