/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 15:02:33 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/07 17:40:40 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

#define WIDTH 800
#define HEIGHT 800

typedef struct s_z
{
	double	real;
	double	imaginary;
}	t_z;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	char		*name;
	double		real_width;
	int			precision;
	t_z			c;
	t_z			original_c;
	t_z			center;
	int			exp;
	int			c_inv;
	int			color_shift;
	int			jump;
}	t_data;

int	ft_strcmp(char *s1, char *s2);	//utils
t_z	mul_z(t_z z1, t_z z2);	// op
t_z	sum_z(t_z z1, t_z z2);	// op
t_z	div_z(t_z z1, t_z z2);	// op
t_z	variable_funct_apply(t_z n, t_z c, int z_exp, int c_inv); // funct
t_z	funct_apply(t_z n, t_z c);	// funct
int	n_inside(t_z z, t_data *data);	// funct
int	create_trgb(unsigned char t, unsigned char r,
	unsigned char g, unsigned char b);	// mlx
int	color_n_inside(int n, t_data *data); // funct
t_z	pixel_to_z(int x, int y, t_data *data);
double	ft_atof(const char *nptr);	//utils
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);	//mlx
int	print_menu(t_data *data);	//mlx
void	render_fractal(t_data *data);	// fractol
int	ft_strlen(char const *s);	//utils
void	ft_putstr(char *s);	//utils
void	data_build(t_data *data, char **argv);	// fractol
int	esc(t_data *data);	// commands
int	key_down(int keycode, t_data *data);	// commands
int	mouse_hook(int keycode, int x, int y, t_data *data);	// commands

#endif