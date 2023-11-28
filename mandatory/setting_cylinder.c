#include "miniRT.h"

void	set_cylinder_list(t_scene *scene, t_setobj *set, int *id, void *element)
{
	set->object = malloc(sizeof(t_object));
	if (!set->object)
		exit(1);
	set->object->id = *id;
	set->object->type = CYLINDER;
	set->object->element = element;
	set->object->next = NULL;
	if (!scene->objects)
		scene->objects = set->object;
	else
	{
		set->iter = scene->objects;
		while (set->iter->next != NULL)
			set->iter = set->iter->next;
		set->iter->next = set->object;
	}
}

void	cylinder_vec_check(char **res, t_setobj set, char **normal)
{
	if (count_dot(res[1]) != 2 || arr_size(set.center) != 3 \
		|| count_dot(res[2]) != 2 || arr_size(normal) != 3 \
		|| count_dot(res[5]) != 2 || arr_size(set.albedo) != 3)
		error();
	return ;
}

void	cylinder_vec_range(t_cylinder *cylinder)
{
	if (range_check_vector(cylinder->normal.x)
		|| range_check_vector(cylinder->normal.y)
		|| range_check_vector(cylinder->normal.z))
		ratio_error(3);
	if (range_check_color(cylinder->color.x)
		|| range_check_color(cylinder->color.y)
		|| range_check_color(cylinder->color.z))
		ratio_error(2);
	return ;
}

void	set_cylinder(t_scene *scene, char **res, int *id)
{
	t_setobj	set;
	t_cylinder	*cylinder;
	char		**normal;

	cylinder = malloc(sizeof(t_cylinder));
	if (!cylinder)
		error();
	set.center = ft_split(res[1], ',');
	normal = ft_split(res[2], ',');
	set.albedo = ft_split(res[5], ',');
	cylinder_vec_check(res, set, normal);
	cylinder->center = vec(ft_strtod(set.center[0]), \
		ft_strtod(set.center[1]), ft_strtod(set.center[2]));
	cylinder->normal = vec(ft_strtod(normal[0]), \
		ft_strtod(normal[1]), ft_strtod(normal[2]));
	cylinder->radius = ft_strtod(res[3]);
	cylinder->height = ft_strtod(res[4]);
	cylinder->color = vec(ft_strtod(set.albedo[0]), \
		ft_strtod(set.albedo[1]), ft_strtod(set.albedo[2]));
	cylinder_vec_range(cylinder);
	cylinder->color = vec(cylinder->color.x / 255, 
		cylinder->color.y / 255, cylinder->color.z / 255);
	free_all(set.center);
	free_all(set.albedo);
	free_all(normal);
	set_cylinder_list(scene, &set, id, (void *)cylinder);
}
