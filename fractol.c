// gcc *.c -Lminilibx-linux -lmlx -lX11 -lXext -lm

#include "fractol.h"
#define WIDTH 1920
#define HEIGHT 1080

typedef struct	s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct	s_data {
	void	*mlx;
	void	*mlx_win;
	t_img	img;
}				t_data;

int	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	int		temp;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	temp = *(unsigned int*)dst;
	*(unsigned int*)dst = color;
	return (temp);
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

int	esc(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_image(data->mlx, data->img.img);
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		return (0);
	}
}

int	change_background(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	y = 0;
	color = my_mlx_pixel_put(&data->img, x, y, 0x00FF0000) + 100;
	while (x < HEIGHT)
	{
		while (y < WIDTH)
		{
			my_mlx_pixel_put(&data->img, x, y, color);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
}

int	main(void)
{
	t_data data;

	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	data.mlx_win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "Hello world!");
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
	mlx_loop_hook(data.mlx, change_background, &data);
	mlx_hook(data.mlx_win, 2, 1L<<0, esc, &data);
	mlx_loop(data.mlx);
	return (0);
}
