/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 14:35:40 by cfargere          #+#    #+#             */
/*   Updated: 2019/04/12 17:45:27 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "libft/libft.h"
#include "fractol.h"

void	init_mlx(t_fractol *f)
{
	int	osef;

	f->mlx = mlx_init();
	f->w = 1080;
	f->h = 960;
	f->win = mlx_new_window(f->mlx, f->w, f->h, "Fractol");
	f->img = mlx_new_image(f->mlx, f->w, f->h);
	f->buff = mlx_get_data_addr(f->img, &osef, &osef, &osef);
}

void	init_fractals(char *arg, t_fractol *f)
{
	f->zoom = 100;
	f->x1 = -8.4;
	f->x2 = 2.4;
	f->y1 = -4.8;
	f->y2 = 4.8;
	f->image_x = (f->x2 - f->x1) * f->zoom;
	f->image_y = (f->y2 - f->y1) * f->zoom;
	if (!ft_strcmp(arg, "julia"))
	{
		f->c_r = -0.7;
		f->c_i = 0.27015;
	}
}

void	fill_pixel(int x, int y, t_fractol *f, unsigned int color)
{
	int				i;
	int				j;
	unsigned int	color_n;

	j = 0;
	i = (x + y * f->w) * 4;
	while (j < 4)
	{
		color_n = (color >> (8 * j)) & 0xff;
		f->buff[i] = color_n;
		j++;
		i++;
	}
}

int		parse_arg(char *arg, t_fractol *f)
{
	if (!ft_strcmp(arg, "mandelbrot") || !ft_strcmp(arg, "julia") ||
			!ft_strcmp(arg, "burningship"))
	{
		init_mlx(f);
		init_fractals(arg, f);
	}
	if (!ft_strcmp(arg, "mandelbrot"))
	{
		f->fractal_nr = 1;
		mandelbrot_pthread(f);
	}
	else if (!ft_strcmp(arg, "julia"))
	{
		f->fractal_nr = 2;
		julia_pthread(f);
	}
	else if (!ft_strcmp(arg, "burningship"))
	{
		f->fractal_nr = 3;
		burningship_pthread(f);
	}
	else
		return (-1);
	return (0);
}

int		main(int ac, char **av)
{
	t_fractol f;

	if (ac != 2)
		ft_putstr("Usage: ./fractol [mandelbrot/julia/burningship]\n");
	else
	{
		if (parse_arg(av[ac - 1], &f) == -1)
		{
			ft_putstr("Usage: ./fractol [mandelbrot/julia/burningship]\n");
			return (0);
		}
		mlx_do_key_autorepeaton(f.mlx);
		mlx_hook(f.win, 6, (1L << 6), &mouse_motion_hook, &f);
		mlx_hook(f.win, 2, (1L << 0), &key_hooks, &f);
		mlx_hook(f.win, 17, (1L << 17), &exit_hook, &f);
		mlx_mouse_hook(f.win, &mouse_hooks, &f);
		mlx_loop(f.mlx);
	}
	return (0);
}
