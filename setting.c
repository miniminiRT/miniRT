#include "miniRT.h"

void	set_size(t_scene *scene)
{
	scene->size.aspect_ratio = 16.0 / 9.0;
	scene->size.width = 1000;
	scene->size.height
		= (int)((double)scene->size.width / scene->size.aspect_ratio);
	return ;
}

void	set_viewport(t_scene *scene)
{
	double	theta;
	double	h;

	theta = (scene->camera.fov * M_PI) / 180.0;
	h = tan(theta / 2);
	scene->viewport.focal_length = 1.0;
	scene->viewport.height = 2.0 * h * scene->viewport.focal_length;
	scene->viewport.width = scene->size.aspect_ratio * scene->viewport.height;
	return ;
}

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

void	set_lights(t_scene *scene, char **res)
{
	t_light	*lights;
	t_light	*iter;
	char	**origin;
	char	**light_color;

	lights = malloc(sizeof(t_light));
	if (!lights)
		exit(1);
	origin = ft_split(res[1], ',');
	light_color = ft_split(res[3], ',');
	lights->origin
		= vec(ft_strtod(origin[0]), ft_strtod(origin[1]), ft_strtod(origin[2]));
	lights->brightness = ft_strtod(res[2]);
	printf("light : %f\n", lights->brightness);
	lights->light_color = vec(ft_strtod(light_color[0]) \
		, ft_strtod(light_color[1]), ft_strtod(light_color[2]));
	printf("light color : %f, %f, %f\n", lights->light_color.x, lights->light_color.y, lights->light_color.z);
	lights->next = NULL;
	free_all(origin);
	free_all(light_color);
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

void set_objects(t_scene *scene, char **res, int *id)
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

void	init_scene(t_scene *scene)
{
	scene->objects = NULL;
	scene->lights = NULL;
	return ;
}

t_scene set_scene(void)
{
	t_scene	scene;
	char	*str;
	char	**res;
	int		fd;
	int		id;

	id = 0;
	fd = open("example.rt", O_RDONLY);
	str = get_next_line(fd);
	init_scene(&scene);
	while (str)
	{
		str = ft_strtrim(str, "\n");
		res = ft_split(str, ' ');
		// if (invalid_input(res))
		// 	exit(1);
		if (ft_strncmp(res[0], "A", 1) == 0)
			set_ambient(&scene, res);
		else if (ft_strncmp(res[0], "C", 1) == 0)
			set_camera(&scene, res);
		else if (ft_strncmp(res[0], "L", 1) == 0)
			set_lights(&scene, res);
		else
			set_objects(&scene, res, &id);
		free(str);
		free_all(res);
		str = get_next_line(fd);
	}
	set_size(&scene);
	set_viewport(&scene);
	return (scene);
}
