/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_sphere.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:05:45 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/28 17:05:48 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	set_sphere_list(t_scene *scene, t_setobj *set, int *id, void *element)
{
	set->object = malloc(sizeof(t_object));
	if (!set->object)
		malloc_error();
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

void	sphere_vec_check(char **res, t_setobj set)
{
	if (count_dot(res[1]) != 2 || arr_size(set.center) != 3 \
		|| count_dot(res[3]) != 2 || arr_size(set.albedo) != 3)
		three_input_error();
	if (tp_arr_size(res) != 4)
		input_arg_count_error();
	return ;
}

void	set_sphere(t_scene *scene, char **res, int *id)
{
	t_sphere	*sphere;
	t_setobj	set;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		malloc_error();
	set.center = ft_split(res[1], ',');
	sphere->center = vec(ft_strtod(set.center[0]), \
		ft_strtod(set.center[1]), ft_strtod(set.center[2]));
	sphere->radius = ft_strtod(res[2]) / 2;
	set.albedo = ft_split(res[3], ',');
	sphere_vec_check(res, set);
	sphere->albedo = vec(ft_strtod(set.albedo[0]) / 255, \
		ft_strtod(set.albedo[1]) / 255, ft_strtod(set.albedo[2]) / 255);
	if (range_check_color(sphere->albedo.x)
		|| range_check_color(sphere->albedo.y)
		|| range_check_color(sphere->albedo.z))
		ratio_error(2);
	free_all(set.albedo);
	free_all(set.center);
	set_sphere_list(scene, &set, id, (void *)sphere);
	return ;
}
