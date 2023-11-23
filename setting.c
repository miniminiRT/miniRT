#include "miniRT.h"

void	set_camera(t_scene *scene, char **res)
{
	char	**origin;
	char	**dir;

	origin = ft_split(res[1], ',');
	if (count_dot(res[1]) != 2 || arr_size(origin) != 3)
		error();
	scene->camera.origin
		= vec(ft_strtod(origin[0]), ft_strtod(origin[1]), ft_strtod(origin[2]));
	dir = ft_split(res[2], ',');
	if (count_dot(res[2]) != 2 || arr_size(dir) != 3)
		error();
	scene->camera.dir
		= vec(ft_strtod(dir[0]), ft_strtod(dir[1]), ft_strtod(dir[2]));
	if (range_check_vector(scene->camera.dir.x)
		|| range_check_vector(scene->camera.dir.y)
		|| range_check_vector(scene->camera.dir.z))
		ratio_error(3);
	scene->camera.fov = ft_strtod(res[3]);
	if (range_check_degree(scene->camera.fov))
		degree_error();
	free_all(origin);
	free_all(dir);
}

void	set_ambient(t_scene *scene, char **res)
{
	char	**color;

	color = ft_split(res[2], ',');
	if (count_dot(res[2]) != 2 || arr_size(color) != 3)
		error();
	scene->ambient.light_ratio = ft_strtod(res[1]);
	if (range_check_light(scene->ambient.light_ratio))
		ratio_error(1);
	scene->ambient.color.x = ft_strtod(color[0]);
	scene->ambient.color.y = ft_strtod(color[1]);
	scene->ambient.color.z = ft_strtod(color[2]);
	if (range_check_color(scene->ambient.color.x)
		|| range_check_color(scene->ambient.color.y)
		|| range_check_color(scene->ambient.color.z))
		ratio_error(2);
	free_all(color);
	return ;
}

void	set_light_list(t_scene *scene, t_light *lights)
{
	t_light	*iter;

	if (!scene->lights)
		scene->lights = lights;
	else
	{
		iter = scene->lights;
		while (iter->next != NULL)
			iter = iter->next;
		iter->next = lights;
	}
}

void	set_lights(t_scene *scene, char **res)
{
	t_light	*lights;
	char	**origin;
	char	**color;

	lights = malloc(sizeof(t_light));
	if (!lights)
		exit(1);
	origin = ft_split(res[1], ',');
	if (count_dot(res[1]) != 2 || arr_size(origin) != 3)
		error();
	color = ft_split(res[3], ',');
	if (count_dot(res[3]) != 2 || arr_size(color) != 3)
		error();
	lights->origin
		= vec(ft_strtod(origin[0]), ft_strtod(origin[1]), ft_strtod(origin[2]));
	lights->brightness = ft_strtod(res[2]);
	if (range_check_light(lights->brightness))
		ratio_error(1);
	lights->light_color = vec(ft_strtod(color[0]), \
		ft_strtod(color[1]), ft_strtod(color[2]));
	if (range_check_color(lights->light_color.x)
		|| range_check_color(lights->light_color.y)
		|| range_check_color(lights->light_color.z))
		ratio_error(2);
	lights->next = NULL;
	free_all(origin);
	free_all(color);
	set_light_list(scene, lights);
}

void	set_objects(t_scene *scene, char **res, int *id)
{
	if (ft_strncmp(res[0], "sp", 2) == 0)
		set_sphere(scene, res, id);
	else if (ft_strncmp(res[0], "pl", 2) == 0)
		set_plane(scene, res, id);
	else if (ft_strncmp(res[0], "cy", 2) == 0)
		set_cylinder(scene, res, id);
	(*id)++;
	return ;
}

