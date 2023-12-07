/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:41:12 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/06 16:44:43 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define WIDTH 800
#define HEIGHT 800

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

t_z	sum_z(t_z z1, t_z z2)
{
	t_z	result;

	result.real = z1.real * z2.real - z1.imaginary * z2.imaginary;
	result.imaginary = z1.real * z2.imaginary + z1.imaginary * z2.real;
	return (result);
}

t_z	mul_z(t_z z1, t_z z2)
{
	t_z	result;

	result.real = z1.real + z2.real;
	result.imaginary = z1.imaginary + z2.imaginary;
	return (result);
}

t_z	div_z(t_z z1, t_z z2)
{
	t_z	result;

	result.real = (z1.real * z2.real + z1.imaginary * z1.imaginary) / (z1.imaginary * z1.imaginary + z2.imaginary * z2.imaginary);
	result.imaginary = (-z1.real * z2.imaginary + z1.imaginary * z2.real) / (z1.imaginary * z1.imaginary + z2.imaginary * z2.imaginary);
	return (result);
}

t_z	variable_funct_apply(t_z n, t_z c, int z_exp, int c_inv)
{
	t_z	z_powered;
	t_z	unit;
	int	i;

	z_powered = n;
	i = 1;
	while (i < z_exp)
	{
		z_powered = mul_z(z_powered, n);
	}
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

double	z_length_q(t_z n)
{
	return (n.real * n.real + n.imaginary * n.imaginary);
}

int	n_inside(t_z n, t_z c, int max_cycles)
{
	int	i;

	i = 0;
	while (i < max_cycles)
	{
		if (z_length_q(n) > 4)
			break;
		n = funct_apply(n, c);
		i++;
	}
	return (i);
}

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

int	color_n_inside(int n, t_data *data)
{
	n += data->color_shift;
	n %= 6 * 255 / data->jump;
	if (n < 255 / data->jump)
		return (create_trgb(0, 255, 0, n * data->jump));
	else if(n < 2 * 255 / data->jump)
		return (create_trgb(0, 255 - (n % (255 / data->jump)) * data->jump, 0, 255));
	else if(n < 3 * 255 / data->jump)
		return (create_trgb(0, 0, (n % (255 / data->jump)) * data->jump, 255));
	else if(n < 4 * 255 / data->jump)
		return (create_trgb(0, 0, 255, 255 - (n % (255 / data->jump)) * data->jump));
	else if(n < 5 * 255 / data->jump)
		return (create_trgb(0, (n % (255 / data->jump)) * data->jump, 255, 0));
	else
		return (create_trgb(0, 255, 255 - (n % (255 / data->jump)) * data->jump, 0));
}

t_z	pixel_to_z(int x, int y, t_data *data)
{
	double	pixel_unit;
	t_z	z;

	pixel_unit = data->real_width / WIDTH;
	z.real = (x - WIDTH / 2) * pixel_unit - data->center.real;
	z.imaginary = (y - HEIGHT / 2) * pixel_unit - data->center.imaginary;
	return (z);
}

double	ft_atof(const char *nptr)
{
	int		i;
	int		n;
	int		dot;
	double	res;

	n = 0;
	i = 1;
	res = 0;
	while ((nptr[n] >= 9 && nptr[n] <= 13) || nptr[n] == ' ')
		n += 1;
	if (nptr[n] == '-' || nptr[n] == '+')
	{
		if (nptr[n] == '-')
			i *= -1;
		n += 1;
	}
	dot = 0;
	while ((nptr[n] >= '0' && nptr[n] <= '9') || nptr[n] == '.')
	{
		if (nptr[n] == '.')
			dot = 1;
		else if (!dot)
			res = res * 10 + (nptr[n] - '0');
		else
		{
			res += (nptr[n] - '0') / pow(10, dot);
			dot++;
		}
		n++;
	}
	return (res * i);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	print_menu(t_data *data)
{
	mlx_string_put(data->mlx, data->mlx_win, 4, 12, 0x00AFAFAF, "COMMANDS:");
	mlx_string_put(data->mlx, data->mlx_win, 4, 30, 0x00FFFFFF, "Esc: exit");
	mlx_string_put(data->mlx, data->mlx_win, 4, 45, 0x00FFFFFF, "Arrows: move");
	mlx_string_put(data->mlx, data->mlx_win, 4, 60, 0x00FFFFFF, "Mouse scroll: zoom");
	mlx_string_put(data->mlx, data->mlx_win, 4, 75, 0x00FFFFFF, "Click on mouse wheel: reset zoom");
	mlx_string_put(data->mlx, data->mlx_win, 4, 90, 0x00FFFFFF, "C: move colors");
	mlx_string_put(data->mlx, data->mlx_win, 4, 105, 0x00FFFFFF, "X: increase distance between colors");
	mlx_string_put(data->mlx, data->mlx_win, 4, 120, 0x00FFFFFF, "Z: decrease distance between colors");
	mlx_string_put(data->mlx, data->mlx_win, 4, 135, 0x00FFFFFF, "Y: increase precision");
	mlx_string_put(data->mlx, data->mlx_win, 4, 150, 0x00FFFFFF, "T: decrease precision");
	if(data->name[0] == 'J')
	{
		mlx_string_put(data->mlx, data->mlx_win, 4, 165, 0x00FFFFFF, "D: increase c's real part");
		mlx_string_put(data->mlx, data->mlx_win, 4, 180, 0x00FFFFFF, "A: decrease c's real part");
		mlx_string_put(data->mlx, data->mlx_win, 4, 195, 0x00FFFFFF, "W: increase c's imaginary part");
		mlx_string_put(data->mlx, data->mlx_win, 4, 210, 0x00FFFFFF, "S: decrease c's imaginary part");
		mlx_string_put(data->mlx, data->mlx_win, 4, 225, 0x00FFFFFF, "R: reset c's values");
	}
	return (0);
}

void	render_fractal(t_data *data)
{
	int	x;
	int	y;
	int	color;
	t_z	z;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			z = pixel_to_z(x, y, data);
			if (data->name[0] == 'M')
				data->c = z;
			color = color_n_inside(n_inside(z, data->c, data->precision), data);
			my_mlx_pixel_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

int	ft_strlen(char const *s)
{
	int	l;

	l = 0;
	while (s && s[l])
		l++;
	return (l);
}

void	ft_putstr(char *s)
{
	if (s)
	{
		if(write(1, s, ft_strlen(s)))
			s += 0;
	}
}

void	data_build(t_data *data, char **argv)
{
	data->name = argv[1];
	data->c.real = 0.33;
	data->c.imaginary = 0.33;
	if (argv[2] && argv[3] && data->name[0] == 'J')
	{
		data->c.real = ft_atof(argv[2]);
		data->c.imaginary = ft_atof(argv[3]);
	}
	data->original_c = data->c;
	data->mlx = mlx_init();
	if (!data->mlx)
		exit(EXIT_FAILURE);
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, data->name);
	if (!data->mlx_win)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img.img)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		exit(EXIT_FAILURE);
	}
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
								&data->img.line_length, &data->img.endian);
	data->real_width = 3;
	data->center.real = 0.7;
	if (data->name[0] == 'J')
		data->center.real = 0;
	data->center.imaginary = 0;
	data->precision = 150;
	data->color_shift = 0;
	data->jump = 15;
}

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

int	main(int argc, char **argv)
{
	t_data	data;

	if (!((argc == 2 && !ft_strcmp(argv[1], "Mandelbrot"))
		|| ((argc == 4 || argc == 2) && !ft_strcmp(argv[1], "Julia"))))
	{
		ft_putstr("Error\nValid parameters:\nMandelbrot\nJulia\nJulia <real> <imaginary>\n");
		exit(EXIT_FAILURE);
	}
	data_build(&data, argv);
	render_fractal(&data);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_down, &data);
	mlx_hook(data.mlx_win, 17, 0L, esc, &data);
	mlx_mouse_hook(data.mlx_win, mouse_hook, &data);
	mlx_loop_hook(data.mlx, print_menu, &data);
	mlx_loop(data.mlx);
}