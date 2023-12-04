/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:41:12 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/04 19:05:00 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

#define WIDTH 1920
#define HEIGHT 1080
#define C_X 960
#define C_Y 540

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
		write(1, s, ft_strlen(s));
}

void	data_build(t_data	*data)
{
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
	data->real_height = HEIGHT;
}

int	esc(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_FAILURE);
}

int	key_down(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		esc(data);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	get_pixel(t_img img, int x, int y)
{
	char	*color;

	color = img.addr + (y * img.line_length + x * (img.bits_per_pixel / 8));
	return(*(unsigned int*)color);
}

t_z	funct_apply(t_z n, t_z c)
{
	t_z	res;

	res.real = pow(n.real, 2) - pow(n.imaginary, 2) + c.real;
	res.imaginary = 2 * n.real * n.imaginary + c.imaginary;
	return (res);
}

double	z_length(t_z n)
{
	return (sqrt(pow(n.real, 2) + pow(n.imaginary, 2)));
}

int	n_inside(t_z n, t_z c, int max_cycles)
{
	int	i;

	i = 0;
	while (i < max_cycles)
	{
		n = funct_apply(n, c);
		if (z_length(n) > 2)
			break;
		i++;
	}
	return (i);
}

int	color_n_inside(int n)
{
	if (!n)
		return (0x00000000);
	if (n == 1)
		return (0x00FF0000);
	else if (n == 2)
		return (0x0000FF00);
	else if (n == 3)
		return (0x000000FF);
}

t_z	pixel_to_z(int x, int y, double real_height)
{
	double	pixel_unit;
	t_z	new;

	pixel_unit = real_height / HEIGHT;
	new.real = (x - C_X) * pixel_unit;
	new.imaginary = (y - C_Y) * pixel_unit;
}

void	render_fractal(t_data *data, int precision, t_z c)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			//printf("%f %f\n", pixel_to_z(x, y, data->real_height).real, pixel_to_z(x, y, data->real_height).imaginary);
			color = n_inside(pixel_to_z(x, y, data->real_height), c, precision);
			my_mlx_pixel_put(&data->img, x, y, color);
			y++;
		}
		x++;
	}
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;
	int	res;

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
	while (nptr[n] >= '0' && nptr[n] <= '9')
		res = res * 10 + (nptr[n++] - '0');
	return (res * i);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!(argc == 2 && !ft_strcmp(argv[1], "Mandelbrot")
		|| argc == 4 && !ft_strcmp(argv[1], "Julia")))
	{
		ft_putstr("Error\nValid parameters:\nMandelbrot\nJulia <real> <imaginary>\n");
		exit(EXIT_FAILURE);
	}
	data.name = argv[1];
	data_build(&data);
	t_z	c;
	c.real = ft_atoi(argv[2]);
	c.imaginary = ft_atoi(argv[3]);
	render_fractal(&data, 3, c);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_down, &data);
	mlx_loop(data.mlx);
}