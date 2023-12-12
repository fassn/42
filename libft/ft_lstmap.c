/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 22:23:42 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/22 17:38:07 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *newlst;
	t_list *start_newlst;
	t_list *tmp;

	if (!lst)
		return (NULL);
	tmp = lst;
	newlst = f(ft_lstnew(tmp->content, tmp->content_size));
	start_newlst = newlst;
	tmp = tmp->next;
	while (tmp)
	{
		newlst->next = f(ft_lstnew(tmp->content, tmp->content_size));
		newlst = newlst->next;
		tmp = tmp->next;
	}
	return (start_newlst);
}
