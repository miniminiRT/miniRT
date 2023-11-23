#include "miniRT.h"

void	set_plane_list(t_scene *scene, t_setobj *set, int *id, void *element)
{
	set->object = malloc(sizeof(t_object));
	if (!set->object)
		exit(1);
	set->object->id = *id;
	set->object->type = PLANE;
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

void	set_plane(t_scene *scene, char **res, int *id)
{
	char		**normal;
	t_plane		*plane;
	t_setobj	set;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		exit(1);
	set.center = ft_split(res[1], ',');
	if (count_dot(res[1]) != 2 || arr_size(set.center) != 3)
		error();
	normal = ft_split(res[2], ',');
	if (count_dot(res[2]) != 2 || arr_size(normal) != 3)
		error();
	set.albedo = ft_split(res[3], ',');
	if (count_dot(res[3]) != 2 || arr_size(set.albedo) != 3)
		error();
	plane->point = vec(ft_strtod(set.center[0]), \
		ft_strtod(set.center[1]), ft_strtod(set.center[2]));
	plane->normal
		= vec(ft_strtod(normal[0]), ft_strtod(normal[1]), ft_strtod(normal[2]));
	if (range_check_vector(plane->normal.x)
		|| range_check_vector(plane->normal.y)
		|| range_check_vector(plane->normal.z))
		ratio_error(3);
	plane->color = vec(ft_strtod(set.albedo[0]), \
		ft_strtod(set.albedo[1]), ft_strtod(set.albedo[2]));
	if (range_check_color(plane->color.x)
		|| range_check_color(plane->color.y)
		|| range_check_color(plane->color.z))
		ratio_error(2);
	free_all(set.center);
	free_all(normal);
	free_all(set.albedo);
	set_plane_list(scene, &set, id, (void *)plane);
}
