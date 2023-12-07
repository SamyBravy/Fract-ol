/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_for_mlx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 18:56:24 by sdell-er          #+#    #+#             */
/*   Updated: 2023/12/07 18:57:45 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	create_trgb(unsigned char t, unsigned char r,
	unsigned char g, unsigned char b)
{
	return (*(int *)(unsigned char [4]){b, g, r, t});
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
