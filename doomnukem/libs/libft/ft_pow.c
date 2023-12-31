/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/18 19:06:22 by vtouffet          #+#    #+#             */
/*   Updated: 2019/08/20 23:39:20 by stsavida         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int			ft_pow(int x, int p)
{
	int res;
	int i;

	if (p == 0)
		return (1);
	res = x;
	i = 0;
	while (++i < p)
		res *= x;
	return (res);
}
