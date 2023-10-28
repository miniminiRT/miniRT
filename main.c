/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 16:00:00 by seojchoi          #+#    #+#             */
/*   Updated: 2023/10/28 16:02:25 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	t_vars	vars;
	t_data	image;
	t_scene	scene;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 562, "");
	image.img = mlx_new_image(vars.mlx, 1000, 562);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	scene = set_scene();
	print_scene(scene, image);
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
