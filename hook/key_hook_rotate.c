/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:43:55 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/20 12:43:57 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	rotate_left(t_vars *vars, t_scene *update)
{
	update->camera.dir.x -= 1 * (M_PI / 180);
	print_scene(update, vars->image);
}

void	rotate_right(t_vars *vars, t_scene *update)
{
	update->camera.dir.x += 1 * (M_PI / 180);
	print_scene(update, vars->image);
}

void	rotate_up(t_vars *vars, t_scene *update)
{
	update->camera.dir.y += 1 * (M_PI / 180);
	print_scene(update, vars->image);
}

void	rotate_down(t_vars *vars, t_scene *update)
{
	update->camera.dir.y -= 1 * (M_PI / 180);
	print_scene(update, vars->image);
}

void	change_angle(t_vars *vars, int keycode)
{
	if (keycode == ROTATE_LEFT)
		rotate_left(vars, &(vars->update));
	else if (keycode == ROTATE_RIGHT)
		rotate_right(vars, &(vars->update));
	else if (keycode == ROTATE_UP)
		rotate_up(vars, &(vars->update));
	else if (keycode == ROTATE_DOWN)
		rotate_down(vars, &(vars->update));
}
