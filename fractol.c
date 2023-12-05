/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:41:12 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/06 00:11:41 by sdell-er         ###   ########.fr       */
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

int	color_n_inside(int n, t_data data)
{
	double	jump;

	jump = 15;
	n += data.color_shift;
	n %= (int)(255 / jump + (255 / jump + 1) * 5 + 1);
	if (n <= 255 / jump)
		return (create_trgb(0, 255, 0, n * jump));
	else if(n <= 255 / jump + 255 / jump + 1)
		return (create_trgb(0, 255 - (n % (int)(255 / jump + 1)) * jump, 0, 255));
	else if(n <= 255 / jump + (255 / jump + 1) * 2)
		return (create_trgb(0, 0, (n % (int)(255 / jump + 1)) * jump, 255));
	else if(n <= 255 / jump + (255 / jump + 1) * 3)
		return (create_trgb(0, 0, 255, 255 - (n % (int)(255 / jump + 1)) * jump));
	else if(n <= 255 / jump + (255 / jump + 1) * 4)
		return (create_trgb(0, (n % (int)(255 / jump + 1)) * jump, 255, 0));
	else
		return (create_trgb(0, 255, 255 - (n % (int)(255 / jump + 1)) * jump, 0));
}

t_z	pixel_to_z(int x, int y, t_data data)
{
	double	pixel_unit;
	t_z	z;

	pixel_unit = data.real_width / WIDTH;
	z.real = (x - data.o.real) * pixel_unit + pixel_unit / 2;
	z.imaginary = (y - data.o.imaginary) * pixel_unit + pixel_unit / 2;
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
	while (nptr[n] >= '0' && nptr[n] <= '9' || nptr[n] == '.')
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

void	render_fractal(t_data *data)
{
	int	x;
	int	y;
	int	color;
	int	is_mandelbrot;
	t_z	z;

	if (!ft_strcmp(data->name, "Mandelbrot"))
		is_mandelbrot = 1;
	else
		is_mandelbrot = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			z = pixel_to_z(x, y, *data);
			if (is_mandelbrot)
				data->c = z;
			color = color_n_inside(n_inside(z, data->c, data->precision), *data);
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
		write(1, s, ft_strlen(s));
}

void	data_build(t_data *data, char **argv)
{
	data->name = argv[1];
	data->c.real = 0.285;
	data->c.imaginary = 0.285;
	if (argv[2] && argv[3] && !ft_strcmp(data->name, "Julia"))
	{
		data->c.real = ft_atof(argv[2]);
		data->c.imaginary = ft_atof(argv[3]);
	}
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
	data->o.real = 565;
	if (!ft_strcmp(data->name, "Julia"))
		data->o.real = 400;
	data->o.imaginary = HEIGHT / 2;
	data->precision = 120;
	data->color_shift = 0;
}

int	esc(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(EXIT_SUCCESS);
}

double	perc(double n, double p)
{
	return (n * p / 100);
}

int	key_down(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		esc(data);
	if (keysym == XK_Right)
		data->o.real -= perc(data->o.real, 7);
	else if (keysym == XK_Left)
		data->o.real += perc(data->o.real, 7);
	else if (keysym == XK_Up)
		data->o.imaginary += perc(data->o.imaginary, 7);
	else if (keysym == XK_Down)
		data->o.imaginary -= perc(data->o.imaginary, 7);
	else if (keysym == XK_p)
		data->real_width -= perc(data->real_width, 2);
	else if (keysym == XK_o)
		data->real_width += perc(data->real_width, 2);
	else if (keysym == XK_d)
		data->c.real += 0.005;
	else if (keysym == XK_a)
		data->c.real -= 0.005;
	else if (keysym == XK_w)
		data->c.imaginary += 0.005;
	else if (keysym == XK_s)
		data->c.imaginary -= 0.005;
	else if (keysym == XK_r)
		data->precision -= 5;
	else if (keysym == XK_t)
		data->precision += 5;
	else if (keysym == XK_c)
		data->color_shift++;
	render_fractal(data);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!(argc == 2 && !ft_strcmp(argv[1], "Mandelbrot")
		|| (argc == 4 || argc == 2) && !ft_strcmp(argv[1], "Julia")))
	{
		ft_putstr("Error\nValid parameters:\nMandelbrot\nJulia\nJulia <real> <imaginary>\n");
		exit(EXIT_FAILURE);
	}
	data_build(&data, argv);
	render_fractal(&data);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_down, &data);
	mlx_hook(data.mlx_win, 17, 0L, esc, &data);
	mlx_loop(data.mlx);
}