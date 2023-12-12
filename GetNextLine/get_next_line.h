/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:08:28 by cfargere          #+#    #+#             */
/*   Updated: 2018/12/06 19:03:10 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 4

int		get_next_line(const int fd, char **line);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
void	ft_strdel(char **as);

#endif
