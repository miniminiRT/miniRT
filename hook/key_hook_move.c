/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:37:09 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/20 12:42:13 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	move_left_right(t_vars *vars, t_scene *update, int keycode)
{
	if (keycode == MOVE_LEFT)
		update->camera.origin.x -= 1;
	else if (keycode == MOVE_RIGHT)
		update->camera.origin.x += 1;
	print_scene(update, vars->image);
}

void	move_up_down(t_vars *vars, t_scene *update, int keycode)
{
	if (keycode == MOVE_UP)
		update->camera.origin.y += 1;
	else if (keycode == MOVE_DOWN)
		update->camera.origin.y -= 1;
	print_scene(update, vars->image);
}

void	move_front_back(t_vars *vars, t_scene *update, int keycode)
{
	if (keycode == MOVE_FRONT)
		update->camera.origin.z -= 1;
	else if (keycode == MOVE_BACK)
		update->camera.origin.z += 1;
	print_scene(update, vars->image);
}

void	change_location(t_vars *vars, int keycode)
{
	if (keycode == MOVE_LEFT || keycode == MOVE_RIGHT)
		move_left_right(vars, &(vars->update), keycode);
	else if (keycode == MOVE_UP || keycode == MOVE_DOWN)
		move_up_down(vars, &(vars->update), keycode);
	else if (keycode == MOVE_FRONT || keycode == MOVE_BACK)
		move_front_back(vars, &(vars->update), keycode);
}
