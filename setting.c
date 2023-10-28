#include "miniRT.h"

void set_size(t_scene *scene)
{
    scene->size.aspect_ratio = 16.0 / 9.0;
    scene->size.width = 1000;  // mlx랑 통일
    scene->size.height = (int)((double)scene->size.width / scene->size.aspect_ratio);
}

void set_viewport(t_scene *scene)
{

    double theta = (scene->camera.fov * M_PI) / 180.0;
    double h = tan(theta/2);
    scene->viewport.focal_length = 1.0;
    scene->viewport.height = 2.0 * h * scene->viewport.focal_length;
    scene->viewport.width = scene->size.aspect_ratio * scene->viewport.height;
}

void set_camera(t_scene *scene, char **res)
{
	char **origin;
	char **dir;

	origin = ft_split(res[1], ',');
    scene->camera.origin = vec(ft_strtod(origin[0]), ft_strtod(origin[1]), ft_strtod(origin[2]));
    dir = ft_split(res[2], ',');
	scene->camera.dir =  vec(ft_strtod(dir[0]), ft_strtod(dir[1]), ft_strtod(dir[2]));
	scene->camera.fov = ft_strtod(res[3]);
	//free dir, origin
}

void set_ambient(t_scene *scene, char **res)
{
	char **color;

	color = ft_split(res[2], ',');
	scene->ambient.light_ratio = ft_strtod(res[1]); //strtod
    scene->ambient.color.x = ft_strtod(color[0]);
    scene->ambient.color.y = ft_strtod(color[1]);
    scene->ambient.color.z = ft_strtod(color[2]);
	//free color
	return ;
}

void	set_lights(t_scene *scene, char **res)
{
	t_light	*lights;
	char **origin;
	char **light_color;

	lights = malloc(sizeof(t_light));
	if (!lights)
		exit(1);
	origin = ft_split(res[1], ',');
	light_color = ft_split(res[3], ',');
	lights->origin = vec(ft_strtod(origin[0]), ft_strtod(origin[1]), ft_strtod(origin[2]));
	lights->brightness = ft_strtod(res[2]);
	lights->light_color = vec(ft_strtod(light_color[0]), ft_strtod(light_color[1]), ft_strtod(light_color[2]));
	lights->next = NULL;
	if (!scene->lights)
		scene->lights = lights;
	else
	{
		while (scene->lights->next != NULL)
			scene->lights = scene->lights->next;
		scene->lights->next = lights;
	}
	//free 만히 해줘야댐
}

void	set_sphere(t_scene *scene, char **res, int *id)
{
	char	**center;
	t_sphere	*sphere;
	char	**albedo;
	t_object	*object;

	sphere = malloc(sizeof(t_sphere));
	//
	center = ft_split(res[1], ',');
	sphere->center = vec(ft_strtod(center[0]), ft_strtod(center[1]), ft_strtod(center[2]));
	sphere->radius = ft_strtod(res[2]) / 2;
	albedo = ft_split(res[3], ',');
	sphere->albedo = vec(ft_strtod(albedo[0]), ft_strtod(albedo[1]), ft_strtod(albedo[2]));
	if (!scene->objects)
	{
		object = malloc(sizeof(t_object));
		//
		object->id = *id;
		object->type = SPHERE;
		object->element = (void *)sphere;
		object->next = NULL;
		scene->objects = object;
	}
	else
	{
		t_object *tmp = scene->objects;
		while (tmp->next != NULL)
			tmp = tmp->next;
		object = malloc(sizeof(t_object));
		//
		object->id = *id;
		object->type = SPHERE;
		object->element = (void *)sphere;
		object->next = NULL;
		tmp->next = object;
	}
	//프리 많이 해야댐
}

void	set_plane(t_scene *scene, char **res, int *id)
{
	char **point;
	char **normal;
	char **color;
	t_plane	*plane;
	t_object *object;

	plane = malloc(sizeof(t_sphere));
	point = ft_split(res[1], ',');
	normal = ft_split(res[2], ',');
	color = ft_split(res[3], ',');
	plane->point = vec(ft_strtod(point[0]), ft_strtod(point[1]), ft_strtod(point[2]));
	plane->normal = vec(ft_strtod(normal[0]), ft_strtod(normal[1]), ft_strtod(normal[2]));
	plane->color = vec(ft_strtod(color[0]), ft_strtod(color[1]), ft_strtod(color[2]));

	if (!scene->objects)
	{
		object = malloc(sizeof(t_object));
		//
		object->id = *id;
		object->type = PLANE;
		object->element = (void *)plane;
		object->next = NULL;
		scene->objects = object;
	}
	else
	{
		while (scene->objects->next != NULL)
			scene->objects = scene->objects->next;
		object = malloc(sizeof(t_object));
		//
		object->id = *id;
		object->type = PLANE;
		object->element = (void *)plane;
		object->next = NULL;
		scene->objects->next = object;
	}
	//프리 많이 해야댐
}

void	set_cylinder(t_scene *scene, char **res, int *id)
{
	char **center;
	char **normal;
	char **color;
	t_cylinder	*cylinder;
	t_object *object;

	cylinder = malloc(sizeof(t_cylinder));
	center = ft_split(res[1], ',');
	normal = ft_split(res[2], ',');
	color = ft_split(res[5], ',');
	cylinder->center = vec(ft_strtod(center[0]), ft_strtod(center[1]), ft_strtod(center[2]));
	cylinder->normal = vec(ft_strtod(normal[0]), ft_strtod(normal[1]), ft_strtod(normal[2]));
	cylinder->radius = ft_strtod(res[3]);
	cylinder->height = ft_strtod(res[4]);
	cylinder->color = vec(ft_strtod(color[0]), ft_strtod(color[1]), ft_strtod(color[2]));
	if (!scene->objects)
	{
		object = malloc(sizeof(t_object));
		//
		object->id = *id;
		object->type = CYLINDER;
		object->element = (void *)cylinder;
		object->next = NULL;
		scene->objects = object;
	}
	else
	{
		while (scene->objects->next != NULL)
			scene->objects = scene->objects->next;
		object = malloc(sizeof(t_object));
		//
		object->id = *id;
		object->type = CYLINDER;
		object->element = (void *)cylinder;
		object->next = NULL;
		scene->objects->next = object;
	}
	//프리 많이 해야댐
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

}

t_scene set_scene(void)
{
	t_scene scene;
	char    *str;
	char    **res;
	int     fd;
	int		id;

	id = 0;
	fd = open("example.rt", O_RDONLY);
	str = get_next_line(fd);
	init_scene(&scene);
	while (str)
	{
		str = ft_strtrim(str, "\n");
		res = ft_split(str,' ');
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
		//res프리
		str = get_next_line(fd);
	}
	set_size(&scene);
	set_viewport(&scene);
	return (scene);
}
