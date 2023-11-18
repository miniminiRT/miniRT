#include "miniRT.h"

void	set_sphere_list(t_scene *scene, t_setobj *set, int *id, void *element)
{
	set->object = malloc(sizeof(t_object));
	if (!set->object)
		exit(1);
	set->object->id = *id;
	set->object->type = SPHERE;
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

void	set_sphere(t_scene *scene, char **res, int *id)
{
	t_sphere	*sphere;
	t_setobj	set;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		exit(1);
	set.center = ft_split(res[1], ',');
	sphere->center = vec(ft_strtod(set.center[0]), \
		ft_strtod(set.center[1]), ft_strtod(set.center[2]));
	sphere->radius = ft_strtod(res[2]) / 2;
	set.albedo = ft_split(res[3], ',');
	sphere->albedo = vec(ft_strtod(set.albedo[0]), \
		ft_strtod(set.albedo[1]), ft_strtod(set.albedo[2]));
	free_all(set.albedo);
	free_all(set.center);
	set_sphere_list(scene, &set, id, (void *)sphere);
	return ;
}
