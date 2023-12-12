/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 14:16:30 by cfargere          #+#    #+#             */
/*   Updated: 2019/04/12 16:53:59 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <pthread.h>
#include "fractol.h"
#include "libft/libft.h"

void	mandelbrot_calc(t_fractol *f)
{
	unsigned int	i;

	f->c_r = f->x / f->zoom + f->x1;
	f->c_i = f->y / f->zoom + f->y1;
	f->z_r = 0;
	f->z_i = 0;
	i = 0;
	while (f->z_r * f->z_r + f->z_i * f->z_i < 4 && i < ITER_MAX)
	{
		f->tmp = f->z_r;
		f->z_r = f->z_r * f->z_r - f->z_i * f->z_i + f->c_r;
		f->z_i = 2 * f->z_i * f->tmp + f->c_i;
		i++;
	}
	if (i == ITER_MAX)
		fill_pixel(f->x, f->y, f, 0);
	else
		fill_pixel(f->x, f->y, f, 265 * i);
}

void	*mandelbrot(void *tab)
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
			mandelbrot_calc(f);
			f->y++;
		}
		f->x++;
	}
	return (tab);
}

void	mandelbrot_pthread(t_fractol *f)
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
		pthread_create(&thread[i], NULL, mandelbrot, &tab[i]);
		i++;
	}
	while (i--)
		pthread_join(thread[i], NULL);
	mlx_clear_window(f->mlx, f->win);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
