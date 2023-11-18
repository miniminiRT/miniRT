#include "miniRT.h"

void	set_camera(t_scene *scene, char **res)
{
	char	**origin;
	char	**dir;

	origin = ft_split(res[1], ',');
	scene->camera.origin
		= vec(ft_strtod(origin[0]), ft_strtod(origin[1]), ft_strtod(origin[2]));
	dir = ft_split(res[2], ',');
	scene->camera.dir
		= vec(ft_strtod(dir[0]), ft_strtod(dir[1]), ft_strtod(dir[2]));
	scene->camera.fov = ft_strtod(res[3]);
	free_all(origin);
	free_all(dir);
}

void	set_ambient(t_scene *scene, char **res)
{
	char	**color;

	color = ft_split(res[2], ',');
	scene->ambient.light_ratio = ft_strtod(res[1]);
	scene->ambient.color.x = ft_strtod(color[0]);
	scene->ambient.color.y = ft_strtod(color[1]);
	scene->ambient.color.z = ft_strtod(color[2]);
	free_all(color);
	return ;
}

void	set_light_list(t_scene *scene, t_light	*lights)
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
	color = ft_split(res[3], ',');
	lights->origin
		= vec(ft_strtod(origin[0]), ft_strtod(origin[1]), ft_strtod(origin[2]));
	lights->brightness = ft_strtod(res[2]);
	lights->light_color = vec(ft_strtod(color[0]), \
		ft_strtod(color[1]), ft_strtod(color[2]));
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
