/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 18:59:05 by cfargere          #+#    #+#             */
/*   Updated: 2019/04/12 17:14:45 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>

# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5

# if __APPLE__
#  define ESCAPE_KEY		0x35
#  define UP_ARROW			0x7E
#  define LEFT_ARROW		0x7B
#  define RIGHT_ARROW		0x7C
#  define DOWN_ARROW		0x7D

# elif __linux__
#  define ESCAPE_KEY		0xff1b
#  define UP_ARROW			0xff52
#  define LEFT_ARROW		0xff51
#  define RIGHT_ARROW		0xff53
#  define DOWN_ARROW		0xff54

# endif

# define THREAD				8

# define ITER_MAX			250

typedef struct	s_fractol
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*buff;

	int				w;
	int				h;
	double			image_x;
	double			image_y;

	int				fractal_nr;
	double			x1;
	double			x2;
	double			y1;
	double			y2;
	int				x;
	int				y;
	int				y_max;
	double			zoom;
	double			c_r;
	double			c_i;
	double			z_r;
	double			z_i;
	double			tmp;
}				t_fractol;

/*
** main.c
*/

void			init_mlx(t_fractol *f);
void			init_fractals(char *arg, t_fractol *f);
void			fill_pixel(int x, int y, t_fractol *f, unsigned int color);
int				parse_arg(char *arg, t_fractol *f);

/*
** hooks.c
*/

int				key_hooks(int keycode, t_fractol *f);
int				mouse_motion_hook(int x, int y, t_fractol *f);
int				mouse_hooks(int button, int x, int y, t_fractol *f);
int				exit_hook(t_fractol *f);

/*
** mandelbrot.c
*/

void			mandelbrot_pthread(t_fractol *f);
void			mandelbrot_calc(t_fractol *f);
void			*mandelbrot(void *tab);

/*
** julia.c
*/

void			julia_pthread(t_fractol *f);
void			julia_calc(t_fractol *f);
void			*julia(void *tab);

/*
** burningship.c
*/

void			burningship_calc(t_fractol *f);
void			*burningship(void *tab);
void			burningship_pthread(t_fractol *f);

/*
** zoom.c
*/

double			interpolate(double start, double end, double interpolation);
void			apply_zoom(t_fractol *f, double m_re, double m_im, double zoom);
void			zoom(int button, int x, int y, t_fractol *f);

#endif
