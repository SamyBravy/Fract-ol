/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:58:36 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/07 19:00:27 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	color_n_inside(int n, t_data *data)
{
	n += data->color_shift;
	n %= 6 * 255 / data->jump;
	if (n < 255 / data->jump)
		return (create_trgb(0, 255, 0, n * data->jump));
	else if (n < 2 * 255 / data->jump)
		return (create_trgb(0, 255 - (n % (255 / data->jump))
				* data->jump, 0, 255));
	else if (n < 3 * 255 / data->jump)
		return (create_trgb(0, 0, (n % (255 / data->jump)) * data->jump, 255));
	else if (n < 4 * 255 / data->jump)
		return (create_trgb(0, 0, 255, 255 - (n % (255 / data->jump))
				* data->jump));
	else if (n < 5 * 255 / data->jump)
		return (create_trgb(0, (n % (255 / data->jump)) * data->jump, 255, 0));
	else
		return (create_trgb(0, 255, 255 - (n % (255 / data->jump))
				* data->jump, 0));
}

t_z	pixel_to_z(int x, int y, t_data *data)
{
	double	pixel_unit;
	t_z		z;

	pixel_unit = data->real_width / WIDTH;
	z.real = (x - WIDTH / 2) * pixel_unit - data->center.real;
	z.imaginary = (y - HEIGHT / 2) * pixel_unit - data->center.imaginary;
	return (z);
}

t_z	variable_funct_apply(t_z n, t_z c, int z_exp, int c_inv)
{
	t_z	z_powered;
	t_z	unit;
	int	i;

	z_powered = n;
	i = 1;
	while (i++ < z_exp)
		z_powered = mul_z(z_powered, n);
	if (c_inv)
	{
		unit.real = 1;
		unit.imaginary = 0;
		c = div_z(unit, c);
	}
	return (sum_z(z_powered, c));
}

t_z	funct_apply(t_z n, t_z c)
{
	t_z	res;

	res.real = n.real * n.real - n.imaginary * n.imaginary + c.real;
	res.imaginary = 2 * n.real * n.imaginary + c.imaginary;
	return (res);
}

int	n_inside(t_z z, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->precision)
	{
		if (z.real * z.real + z.imaginary * z.imaginary > 4)
			break ;
		if (data->name[0] != 'C')
			z = funct_apply(z, data->c);
		else
			z = variable_funct_apply(z, data->c, data->exp, data->type);
		i++;
	}
	return (i);
}
