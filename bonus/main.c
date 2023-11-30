/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 15:11:41 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/28 16:51:24 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	my_mlx(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	new_image(t_vars *vars)
{
	mlx_destroy_image(vars->mlx, vars->image.img);
	vars->image.img = mlx_new_image(vars->mlx, 1000, 562);
	vars->image.addr = mlx_get_data_addr(vars->image.img,
			&vars->image.bits_per_pixel,
			&vars->image.line_length, &vars->image.endian);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == MOVE_DOWN || keycode == MOVE_UP
		|| keycode == MOVE_LEFT || keycode == MOVE_RIGHT
		|| keycode == MOVE_FRONT || keycode == MOVE_BACK)
	{
		new_image(vars);
		change_location(vars, keycode);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	}
	if (keycode == ROTATE_UP || keycode == ROTATE_DOWN
		|| keycode == ROTATE_LEFT || keycode == ROTATE_RIGHT)
	{
		new_image(vars);
		change_angle(vars, keycode);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->image.img, 0, 0);
	}
	return (0);
}

int	exit_hook(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;
	t_scene	scene;

	if (argc == 2)
	{
		file_name_check(argv[1]);
		vars.mlx = mlx_init();
		vars.win = mlx_new_window(vars.mlx, 1000, 562, "miniRT");
		vars.image.img = mlx_new_image(vars.mlx, 1000, 562);
		vars.image.addr = \
		mlx_get_data_addr(vars.image.img, &(vars.image.bits_per_pixel),
				&(vars.image.line_length), &(vars.image.endian));
		scene = set_scene(argv[1]);
		vars.update = scene;
		print_scene(&scene, vars.image);
		mlx_put_image_to_window(vars.mlx, vars.win, vars.image.img, 0, 0);
		mlx_key_hook(vars.win, key_hook, &vars);
		mlx_hook(vars.win, 17, 0, exit_hook, &vars);
		mlx_loop(vars.mlx);
	}
	else
		wrong_type_input();
	return (0);
}
