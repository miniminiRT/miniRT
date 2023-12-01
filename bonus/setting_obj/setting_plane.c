/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_plane.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:05:29 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/28 17:05:33 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	set_plane_list(t_scene *scene, t_setobj *set, int *id, void *element)
{
	set->object = malloc(sizeof(t_object));
	if (!set->object)
		malloc_error();
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

void	plane_vec_check(char **res, t_setobj set, char **normal)
{
	if (count_dot(res[1]) != 2 || arr_size(set.center) != 3 \
		|| count_dot(res[2]) != 2 || arr_size(normal) != 3 \
		|| count_dot(res[3]) != 2 || arr_size(set.albedo) != 3)
		three_input_error();
	if (tp_arr_size(res) != 4)
		input_arg_count_error();
	return ;
}

void	plane_vec_range(t_plane *plane)
{
	if (range_check_vector(plane->normal.x)
		|| range_check_vector(plane->normal.y)
		|| range_check_vector(plane->normal.z))
		ratio_error(3);
	if (range_check_color(plane->color.x)
		|| range_check_color(plane->color.y)
		|| range_check_color(plane->color.z))
		ratio_error(2);
	return ;
}

void	set_plane(t_scene *scene, char **res, int *id)
{
	char		**normal;
	t_plane		*plane;
	t_setobj	set;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		malloc_error();
	set.center = ft_split(res[1], ',');
	normal = ft_split(res[2], ',');
	set.albedo = ft_split(res[3], ',');
	plane_vec_check(res, set, normal);
	plane->point = vec(ft_strtod(set.center[0]), \
		ft_strtod(set.center[1]), ft_strtod(set.center[2]));
	plane->normal
		= vec(ft_strtod(normal[0]), ft_strtod(normal[1]), ft_strtod(normal[2]));
	plane->color = vec(ft_strtod(set.albedo[0]) / 255, \
		ft_strtod(set.albedo[1]) / 255, ft_strtod(set.albedo[2]) / 255);
	plane_vec_range(plane);
	free_all(set.center);
	free_all(normal);
	free_all(set.albedo);
	set_plane_list(scene, &set, id, (void *)plane);
}
