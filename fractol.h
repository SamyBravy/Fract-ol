/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:02:33 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/04 18:45:34 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include "minilibx-linux/mlx.h"
#include <X11/keysym.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <unistd.h>

typedef struct	s_z
{
	double real;
    double imaginary;
}				t_z;

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_data
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;
    char	*name;
    double  real_width;
	t_z		c;
	t_z		o;
}				t_data;

#endif