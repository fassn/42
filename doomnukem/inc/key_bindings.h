/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_bindings.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <cfargere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 16:53:11 by cfargere          #+#    #+#             */
/*   Updated: 2019/08/29 00:24:17 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEY_BINDINGS_H
# define KEY_BINDINGS_H

# if __APPLE__
#  define ESCAPE_KEY		53
#  define CTRL_KEY			256
#  define SHIFT_KEY			257
#  define SPACE_KEY			49
#  define KP_MINUS_KEY		78
#  define KP_PLUS_KEY		69
#  define KP_5_KEY			87
#  define UP_ARROW			126
#  define LEFT_ARROW		123
#  define RIGHT_ARROW		124
#  define DOWN_ARROW		125
#  define A_KEY				0
#  define D_KEY				2
#  define E_KEY				14
#  define F_KEY             3
#  define G_KEY				5
#  define M_KEY				46
#  define R_KEY				15
#  define S_KEY				1
#  define W_KEY				13

# elif __linux__
#  define ESCAPE_KEY		0xff1b
#  define CTRL_KEY			0xffe3
#  define SHIFT_KEY			0xffe1
#  define SPACE_KEY			0xff80
#  define KP_MINUS_KEY		0xffad
#  define KP_PLUS_KEY		0xffab
#  define KP_5_KEY			0xffb5
#  define UP_ARROW			0xff52
#  define LEFT_ARROW		0xff51
#  define RIGHT_ARROW		0xff53
#  define DOWN_ARROW		0xff54
#  define A_KEY				0x0061
#  define D_KEY				0x0064
#  define E_KEY				0x0065
#  define F_KEY             0x0066
#  define G_KEY				0x0067
#  define M_KEY				0x006d
#  define R_KEY				0x0072
#  define S_KEY				0x0073
#  define W_KEY				0x0077
# endif

#endif
