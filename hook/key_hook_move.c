
#include "../miniRT.h"

// void print_scene(t_scene scene, t_data image)

// void	move_left(t_vars  *vars, t_scene *scene)
// {

// 	print_scene(scene, vars->image);
// }

// void	move_right(t_vars  *vars, t_scene *scene)
// {
// 	vars->update.origin.x += 1;
// 	re_draw();
// }

// void	move_up(t_vars  *vars, t_scene *scene)
// {
// 	vars->update.origin.y += 1;
// 	re_draw();
// }

// void	move_down(t_vars  *vars, t_scene *scene)
// {
// 	vars->update.origin.y -= 1;
// 	re_draw();
// }

// void	move_front(t_vars  *vars, t_scene *scene)
// {
// 	vars->update.origin.z -= 1;
// 	re_draw();
// }

// void	move_back(t_vars  *vars, t_scene *scene)
// {
// 	vars->update.origin.z += 1;
// 	re_draw();
// }

// void	change_location(t_vars  *vars, t_scene *scene, int keycode)
// {
// 	if (keycode == MOVE_LEFT)  // A
// 		move_left(vars, scene);
// 	else if (keycode == MOVE_RIGHT)  // D
// 		move_right(vars, scene);
// 	else if (keycode == MOVE_UP)  // W
// 		move_up(vars, scene);
// 	else if (keycode == MOVE_DOWN)  // S
// 		move_down(vars, scene);
// 	else if (keycode == MOVE_FRONT)  // Q
// 		move_front(vars, scene);
// 	else if (keycode == MOVE_BACK)  // E
// 		move_back(vars, scene);
// 	else
// 		return ;
// }