#include "miniRT.h"

void	set_plane(t_scene *scene, char **res, int *id)
{
	char		**normal;
	t_plane		*plane;
	t_setobj	set;

	plane = malloc(sizeof(t_sphere));
	set.center = ft_split(res[1], ',');
	normal = ft_split(res[2], ',');
	set.albedo = ft_split(res[3], ',');
	plane->point
		= vec(ft_strtod(set.center[0]), ft_strtod(set.center[1]), ft_strtod(set.center[2]));
	plane->normal
		= vec(ft_strtod(normal[0]), ft_strtod(normal[1]), ft_strtod(normal[2]));
	plane->color
		= vec(ft_strtod(set.albedo[0]), ft_strtod(set.albedo[1]), ft_strtod(set.albedo[2]));
	free_all(set.center);
	free_all(normal);
	free_all(set.albedo);
	if (!scene->objects)
	{
		set.object = malloc(sizeof(t_object));
		if (!set.object)
			exit(1);
		set.object->id = *id;
		set.object->type = PLANE;
		set.object->element = (void *)plane;
		set.object->next = NULL;
		scene->objects = set.object;
	}
	else
	{
		set.iter = scene->objects;
		while (set.iter->next != NULL)
			set.iter = set.iter->next;
		set.object = malloc(sizeof(t_object));
		if (!set.object)
			exit(1);
		set.object->id = *id;
		set.object->type = PLANE;
		set.object->element = (void *)plane;
		set.object->next = NULL;
		set.iter->next = set.object;
	}
}

void	set_cylinder(t_scene *scene, char **res, int *id)
{
	t_setobj	set;
	t_cylinder	*cylinder;
	char		**normal;

	cylinder = malloc(sizeof(t_cylinder));
	set.center = ft_split(res[1], ',');
	normal = ft_split(res[2], ',');
	set.albedo = ft_split(res[5], ',');
	cylinder->center = vec(ft_strtod(set.center[0]), ft_strtod(set.center[1]), ft_strtod(set.center[2]));
	cylinder->normal = vec(ft_strtod(normal[0]), ft_strtod(normal[1]), ft_strtod(normal[2]));
	cylinder->radius = ft_strtod(res[3]);
	cylinder->height = ft_strtod(res[4]);
	cylinder->color = vec(ft_strtod(set.albedo[0]), ft_strtod(set.albedo[1]), ft_strtod(set.albedo[2]));
	if (!scene->objects)
	{
		set.object = malloc(sizeof(t_object));
		if (!set.object)
			exit(1);
		set.object->id = *id;
		set.object->type = CYLINDER;
		set.object->element = (void *)cylinder;
		set.object->next = NULL;
		scene->objects = set.object;
	}
	else
	{
		set.iter = scene->objects;
		while (set.iter->next != NULL)
			set.iter = set.iter->next;
		set.object = malloc(sizeof(t_object));
		if (!set.object)
			exit(1);
		set.object->id = *id;
		set.object->type = CYLINDER;
		set.object->element = (void *) cylinder;
		set.object->next = NULL;
		set.iter->next = set.object;
	}
	free_all(set.center);
	free_all(set.albedo);
	free_all(normal);
}

void	set_sphere(t_scene *scene, char **res, int *id)
{
	t_sphere	*sphere;
	t_setobj	set;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		exit(1);
	set.center = ft_split(res[1], ',');
	sphere->center
		= vec(ft_strtod(set.center[0]), ft_strtod(set.center[1]), ft_strtod(set.center[2]));
	sphere->radius = ft_strtod(res[2]) / 2;
	set.albedo = ft_split(res[3], ',');
	sphere->albedo
		= vec(ft_strtod(set.albedo[0]), ft_strtod(set.albedo[1]), ft_strtod(set.albedo[2]));
	if (!scene->objects)
	{
		set.object = malloc(sizeof(t_object));
		if (!set.object)
			exit(1);
		set.object->id = *id;
		set.object->type = SPHERE;
		set.object->element = (void *)sphere;
		set.object->next = NULL;
		scene->objects = set.object;
	}
	else
	{
		set.iter = scene->objects;
		while (set.iter->next != NULL)
			set.iter = set.iter->next;
		set.object = malloc(sizeof(t_object));
		if (!set.object)
			exit(1);
		set.object->id = *id;
		set.object->type = SPHERE;
		set.object->element = (void *)sphere;
		set.object->next = NULL;
		set.iter->next = set.object;
	}
	free_all(set.albedo);
	free_all(set.center);
	return ;
}
