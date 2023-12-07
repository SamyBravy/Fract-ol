/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:41:24 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/07 17:42:04 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	esc(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

int	key_down(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		esc(data);
	if (keycode == XK_Right)
		data->center.real -= data->real_width * 0.05;
	else if (keycode == XK_Left)
		data->center.real += data->real_width * 0.05;
	else if (keycode == XK_Up)
		data->center.imaginary += data->real_width * 0.05;
	else if (keycode == XK_Down)
		data->center.imaginary -= data->real_width * 0.05;
	else if (keycode == XK_d)
		data->c.real += 0.005;
	else if (keycode == XK_a)
		data->c.real -= 0.005;
	else if (keycode == XK_w)
		data->c.imaginary += 0.005;
	else if (keycode == XK_s)
		data->c.imaginary -= 0.005;
	else if (keycode == XK_r)
		data->c = data->original_c;
	else if (keycode == XK_y)
		data->precision += 10;
	else if (keycode == XK_t)
		data->precision -= 10;
	else if (keycode == XK_c)
		data->color_shift++;
	else if (keycode == XK_z && data->jump > 1)
	{
		if (data->jump <= 5)
			data->jump--;
		else
			data->jump -= 5;
	}
	else if (keycode == XK_x && data->jump <= 125)
	{
		if (data->jump < 5)
			data->jump++;
		else
			data->jump += 5;
	}
	else
		return (0);
	render_fractal(data);
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_data *data)
{
	if (keycode == 4)
	{
		data->center.real -= (x - WIDTH / 2) * data->real_width / WIDTH * 0.05;
		data->center.imaginary -= (y - HEIGHT / 2) * data->real_width / WIDTH * 0.05;
		data->real_width = data->real_width * 0.95;
		data->precision += 1;
	}
	else if (keycode == 5)
	{
		data->real_width = data->real_width * 1.05;
		data->center.real += (x - WIDTH / 2) * data->real_width / WIDTH * 0.05;
		data->center.imaginary += (y - HEIGHT / 2) * data->real_width / WIDTH * 0.05;
		data->precision -= 1;
	}
	else if (keycode == 2)
	{
		data->real_width = 3;
		data->center.real = 0.7;
		if (data->name[0] == 'J')
			data->center.real = 0;
		data->center.imaginary = 0;
		data->precision = 150;
	}
	else
		return (0);
	render_fractal(data);
	return (0);
}
