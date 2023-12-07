// gcc fractol.c -Lminilibx-linux -lmlx -lX11 -lXext -lm -Werror -Wextra -Wall -O3

#include "fractol.h"
#define WIDTH 1920
#define HEIGHT 1080

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

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
}

unsigned char	get_t(int trgb)
{
	return (((unsigned char *)&trgb)[3]);
}

unsigned char	get_r(int trgb)
{
	return (((unsigned char *)&trgb)[2]);
}

unsigned char	get_g(int trgb)
{
	return (((unsigned char *)&trgb)[1]);
}

unsigned char	get_b(int trgb)
{
	return (((unsigned char *)&trgb)[0]);
}

void	change_background(t_data *data)
{
	int	x;
	int	y;
	int	color;

	if (get_pixel(data->img, 1, 1) == 0x00FF0000)
		color = 0x0000FF00;
	else if (get_pixel(data->img, 1, 1) == 0x0000FF00)
		color = 0x000000FF;
	else
		color = 0x00FF0000;
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			my_mlx_pixel_put(&data->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

int	esc(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->mlx_win);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
}

int	key_down(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		esc(data);
	else
		change_background(data);
}

int	main(void)
{
	t_data data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Fract-ol");
	if (!data.mlx_win)
	{
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (1);
	}
	data.img.img = mlx_new_image(data.mlx, WIDTH, HEIGHT);
	if (!data.img.img)
	{
		mlx_destroy_window(data.mlx, data.mlx_win);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		return (1);
	}
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
								&data.img.line_length, &data.img.endian);
	mlx_hook(data.mlx_win, 2, 1L<<0, key_down, &data);
	mlx_loop(data.mlx);
	return (0);
}
