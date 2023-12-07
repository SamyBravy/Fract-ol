/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:41:12 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/07 19:43:01 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

static void	build_parameters(t_data *data, char **argv)
{
	data->c.real = 0.33;
	data->c.imaginary = 0.33;
	if (argv[2] && argv[3] && data->name[0] == 'J')
	{
		data->c.real = ft_atof(argv[2]);
		data->c.imaginary = ft_atof(argv[3]);
	}
	data->original_c = data->c;
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

void	data_build(t_data *data, char **argv)
{
	data->name = argv[1];
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
	build_parameters(data, argv);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!((argc == 2 && !ft_strcmp(argv[1], "Mandelbrot"))
			|| ((argc == 4 || argc == 2) && !ft_strcmp(argv[1], "Julia"))
			|| (argc == 4 && !ft_strcmp(argv[1], "Custom"))))
	{
		ft_putstr("Error\nValid parameters:\nMandelbrot\nJulia\n");
		ft_putstr("Julia <real> <imaginary>\nCustom <z_exp> <is_c_inverted>\n");
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
