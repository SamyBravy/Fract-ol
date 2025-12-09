/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdell-er <sdell-er@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:00:59 by sdell-er          #+#    #+#             */
/*   Updated: 2024/01/02 16:36:46 by sdell-er         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

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

	result.real = (z1.real * z2.real + z1.imaginary * z2.imaginary)
		/ (z2.real * z2.real + z2.imaginary * z2.imaginary);
	result.imaginary = (-z1.real * z2.imaginary + z1.imaginary * z2.real)
		/ (z2.real * z2.real + z2.imaginary * z2.imaginary);
	return (result);
}
