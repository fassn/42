/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burningship.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:18:18 by cfargere          #+#    #+#             */
/*   Updated: 2019/04/12 16:28:23 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <pthread.h>
#include <math.h>
#include "fractol.h"
#include "libft/libft.h"

void	burningship_calc(t_fractol *f)
{
	unsigned int	i;

	f->c_r = f->x / f->zoom + f->x1;
	f->c_i = f->y / f->zoom + f->y1;
	f->z_r = 0;
	f->z_i = 0;
	i = 0;
	while (f->z_r * f->z_r + f->z_i * f->z_i < 4 && i < ITER_MAX)
	{
		f->tmp = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
		f->z_i = fabs(2.0 * f->z_r * f->z_i) + f->c_i;
		f->z_r = fabs(f->tmp);
		i++;
	}
	if (i == ITER_MAX)
		fill_pixel(f->x, f->y, f, 0);
	else
		fill_pixel(f->x, f->y, f, 265 * i);
}

void	*burningship(void *tab)
{
	t_fractol	*f;
	int			tmp;

	f = (t_fractol *)tab;
	f->x = 0;
	tmp = f->y;
	while (f->x < f->image_x)
	{
		f->y = tmp;
		while (f->y < f->y_max)
		{
			burningship_calc(f);
			f->y++;
		}
		f->x++;
	}
	return (tab);
}

void	burningship_pthread(t_fractol *f)
{
	t_fractol	tab[THREAD];
	pthread_t	thread[THREAD];
	int			i;
	int			thread_size;

	i = 0;
	thread_size = f->h / THREAD;
	while (i < THREAD)
	{
		ft_memcpy((void *)&tab[i], (void *)f, sizeof(t_fractol));
		tab[i].y = thread_size * i;
		tab[i].y_max = thread_size * (i + 1);
		pthread_create(&thread[i], NULL, burningship, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(thread[i], NULL);
	mlx_clear_window(f->mlx, f->win);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
