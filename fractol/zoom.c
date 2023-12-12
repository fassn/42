/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 18:56:28 by cfargere          #+#    #+#             */
/*   Updated: 2019/04/12 15:58:25 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

void	apply_zoom(t_fractol *f, double m_re, double m_im, double zoom)
{
	double interpolation;

	interpolation = 1.0 / zoom;
	f->x1 = interpolate(m_re, f->x1, interpolation);
	f->y1 = interpolate(m_im, f->y1, interpolation);
	f->x2 = interpolate(m_re, f->x2, interpolation);
	f->y2 = interpolate(m_im, f->y2, interpolation);
}

void	zoom(int button, int x, int y, t_fractol *f)
{
	double mouse_re;
	double mouse_im;

	mouse_re = (double)x / ((double)f->w / (f->x2 - f->x1)) + f->x1;
	mouse_im = (double)y / (f->h / (f->y2 - f->y1)) + f->y1;
	if (button == MOUSE_SCROLL_UP)
	{
		apply_zoom(f, mouse_re, mouse_im, 1.5);
		f->zoom *= 1.5;
	}
	if (button == MOUSE_SCROLL_DOWN)
	{
		apply_zoom(f, mouse_re, mouse_im, 1 / 1.5);
		f->zoom *= 1 / 1.5;
	}
}
