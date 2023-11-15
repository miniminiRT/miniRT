
#include "../miniRT.h"

void	move_left(t_vars  *vars, t_scene *update)
{
	update->camera.origin.x -= 1;
	print_scene(update, vars->image);
}

void	move_right(t_vars  *vars, t_scene *update)
{
	update->camera.origin.x += 1;
	print_scene(update, vars->image);
}

void	move_up(t_vars  *vars, t_scene *update)
{
	update->camera.origin.y += 1;
	print_scene(update, vars->image);
}

void	move_down(t_vars  *vars, t_scene *update)
{
	update->camera.origin.y -= 1;
	print_scene(update, vars->image);
}

void	move_front(t_vars  *vars, t_scene *update)
{
	update->camera.origin.z -= 1;
	print_scene(update, vars->image);
}

void	move_back(t_vars  *vars, t_scene *update)
{
	update->camera.origin.z += 1;
	print_scene(update, vars->image);
}

void	change_location(t_vars  *vars, int keycode)
{
	if (keycode == MOVE_LEFT)  // A
		move_left(vars, &(vars->update));
	else if (keycode == MOVE_RIGHT)  // D
		move_right(vars, &(vars->update));
	else if (keycode == MOVE_UP)  // W
		move_up(vars, &(vars->update));
	else if (keycode == MOVE_DOWN)  // S
		move_down(vars, &(vars->update));
	else if (keycode == MOVE_FRONT)  // Q
		move_front(vars, &(vars->update));
	else if (keycode == MOVE_BACK)  // E
		move_back(vars, &(vars->update));
	else
		return ;
}