/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:41:12 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/07 17:41:59 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"




t_z	mul_z(t_z z1, t_z z2)
{
	t_z	result;

	result.real = z1.real * z2.real - z1.imaginary * z2.imaginary;
	result.imaginary = z1.real * z2.imaginary + z1.imaginary * z2.real;
	return (result);
}

t_z	sum_z(t_z z1, t_z z2)
{
	t_z	result;

	result.real = z1.real + z2.real;
	result.imaginary = z1.imaginary + z2.imaginary;
	return (result);
}

t_z	div_z(t_z z1, t_z z2)
{
	t_z	result;

	result.real = (z1.real * z2.real + z1.imaginary * z1.imaginary)
		/ (z2.real * z2.real + z2.imaginary * z2.imaginary);
	result.imaginary = (-z1.real * z2.imaginary + z1.imaginary * z2.real)
		/ (z2.real * z2.real + z2.imaginary * z2.imaginary);
	return (result);
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
			z = variable_funct_apply(z, data->c, data->exp, data->c_inv);
		i++;
	}
	return (i);
}

int	create_trgb(unsigned char t, unsigned char r,
	unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

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



void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	print_menu(t_data *data)
{
	int		i;
	char	*str[14];

	mlx_string_put(data->mlx, data->mlx_win, 4, 12, 0x00AFAFAF, "COMMANDS:");
	str[0] = "Esc: exit";
	str[1] = "Arrows: move";
	str[2] = "Mouse scroll: zoom";
	str[3] = "Click on mouse wheel: reset zoom";
	str[4] = "C: move colors";
	str[5] = "X: increase distance between colors";
	str[6] = "Z: decrease distance between colors";
	str[7] = "Y: increase precision";
	str[8] = "T: decrease precision";
	str[9] = "D: increase c's real part";
	str[10] = "A: decrease c's real part";
	str[11] = "W: increase c's imaginary part";
	str[12] = "S: decrease c's imaginary part";
	str[13] = "R: reset c's values";
	i = 1;
	while (++i * 15 <= 150 + 75 * (data->name[0] == 'J'))
		mlx_string_put(data->mlx, data->mlx_win, 4, i * 15,
			0x00FFFFFF, str[i - 2]);
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
			if (data->name[0] != 'J')
				data->c = z;
			color = color_n_inside(n_inside(z, data), data);
			my_mlx_pixel_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}



void	ft_putstr(char *s)
{
	if (s)
	{
		if (write(1, s, ft_strlen(s)))
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
	data->exp = 2;
	data->c_inv = 0;
	if (data->name[0] == 'C')
	{
		data->exp = atof(argv[2]);
		data->c_inv = atof(argv[3]);
	}
}



int	main(int argc, char **argv)
{
	t_data	data;

	if (!((argc == 2 && !ft_strcmp(argv[1], "Mandelbrot"))
			|| ((argc == 4 || argc == 2) && !ft_strcmp(argv[1], "Julia"))
			|| (argc == 4 && !ft_strcmp(argv[1], "Custom"))))
	{
		ft_putstr("Error\nValid parameters:\nMandelbrot\nJulia\
			Julia <real> <imaginary>\nCustom <exp> <is_c_inverted>\n");
		exit(EXIT_FAILURE);
	}
	data_build(&data, argv);
	render_fractal(&data);
	mlx_hook(data.mlx_win, 2, 1L << 0, key_down, &data);
	mlx_hook(data.mlx_win, 17, 0L, esc, &data);
	mlx_mouse_hook(data.mlx_win, mouse_hook, &data);
	mlx_loop_hook(data.mlx, print_menu, &data);
	mlx_loop(data.mlx);
}
