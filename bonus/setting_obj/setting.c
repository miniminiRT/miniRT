/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:05:53 by seojchoi          #+#    #+#             */
/*   Updated: 2023/12/01 12:35:19 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	set_camera(t_scene *scene, char **res)
{
	char	**origin;
	char	**dir;

	origin = ft_split(res[1], ',');
	if (tp_arr_size(res) != 4)
		input_arg_count_error();
	if (count_dot(res[1]) != 2 || arr_size(origin) != 3)
		three_input_error();
	scene->camera.origin
		= vec(ft_strtod(origin[0]), ft_strtod(origin[1]), ft_strtod(origin[2]));
	dir = ft_split(res[2], ',');
	if (count_dot(res[2]) != 2 || arr_size(dir) != 3)
		three_input_error();
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
		three_input_error();
	if (tp_arr_size(res) != 3)
		input_arg_count_error();
	scene->ambient.light_ratio = ft_strtod(res[1]);
	if (range_check_light(scene->ambient.light_ratio))
		ratio_error(1);
	scene->ambient.color.x = ft_strtod(color[0]) / 255;
	scene->ambient.color.y = ft_strtod(color[1]) / 255;
	scene->ambient.color.z = ft_strtod(color[2]) / 255;
	if (range_check_color(scene->ambient.color.x)
		|| range_check_color(scene->ambient.color.y)
		|| range_check_color(scene->ambient.color.z))
		ratio_error(2);
	free_all(color);
	return ;
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

void	set_viewport(t_scene *scene)
{
	scene->viewport.focal_length = 1.0;
	scene->viewport.height = 2.0 * tan(scene->camera.fov / 360 * M_PI);
	scene->viewport.width = scene->size.aspect_ratio * scene->viewport.height;
	return ;
}
