/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 16:53:25 by cfargere          #+#    #+#             */
/*   Updated: 2019/04/12 16:38:35 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "fractol.h"

int		key_hooks(int keycode, t_fractol *f)
{
	if (keycode == ESCAPE_KEY)
	{
		mlx_clear_window(f->mlx, f->win);
		mlx_destroy_image(f->mlx, f->img);
		mlx_destroy_window(f->mlx, f->win);
		exit(0);
	}
	if (keycode == UP_ARROW)
		f->y1 += 0.05;
	if (keycode == DOWN_ARROW)
		f->y1 -= 0.05;
	if (keycode == LEFT_ARROW)
		f->x1 += 0.05;
	if (keycode == RIGHT_ARROW)
		f->x1 -= 0.05;
	if (f->fractal_nr == 1)
		mandelbrot_pthread(f);
	if (f->fractal_nr == 2)
		julia_pthread(f);
	if (f->fractal_nr == 3)
		burningship_pthread(f);
	return (0);
}

int		mouse_motion_hook(int x, int y, t_fractol *f)
{
	static int	prev_y;
	static int	prev_x;

	if (f->fractal_nr == 2)
	{
		if (prev_y < y)
			f->c_r += 0.001;
		if (prev_y > y)
			f->c_r -= 0.001;
		if (prev_x < x)
			f->c_i += 0.001;
		if (prev_x > x)
			f->c_i -= 0.001;
		julia_pthread(f);
	}
	prev_y = y;
	prev_x = x;
	return (0);
}

int		mouse_hooks(int button, int x, int y, t_fractol *f)
{
	zoom(button, x, y, f);
	if (f->fractal_nr == 1)
		mandelbrot_pthread(f);
	if (f->fractal_nr == 2)
		julia_pthread(f);
	if (f->fractal_nr == 3)
		burningship_pthread(f);
	return (0);
}

int		exit_hook(t_fractol *f)
{
	mlx_clear_window(f->mlx, f->win);
	mlx_destroy_image(f->mlx, f->img);
	mlx_destroy_window(f->mlx, f->win);
	exit(0);
}
