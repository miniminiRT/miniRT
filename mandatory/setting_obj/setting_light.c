/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:05:22 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/28 17:05:24 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	set_light_list(t_scene *scene, t_light *lights)
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

void	light_vec_check(char **res, char **origin, char **color)
{
	if (count_dot(res[1]) != 2 || arr_size(origin) != 3)
		three_input_error();
	if (count_dot(res[3]) != 2 || arr_size(color) != 3)
		three_input_error();
	if (tp_arr_size(res) != 4)
		input_arg_count_error();
	return ;
}

void	set_lights(t_scene *scene, char **res)
{
	t_light	*lights;
	char	**origin;
	char	**color;

	lights = malloc(sizeof(t_light));
	if (!lights)
		malloc_error();
	origin = ft_split(res[1], ',');
	color = ft_split(res[3], ',');
	light_vec_check(res, origin, color);
	lights->origin
		= vec(ft_strtod(origin[0]), ft_strtod(origin[1]), ft_strtod(origin[2]));
	lights->brightness = ft_strtod(res[2]);
	if (range_check_light(lights->brightness))
		ratio_error(1);
	lights->light_color = vec(ft_strtod(color[0]) / 255, \
		ft_strtod(color[1]) / 255, ft_strtod(color[2]) / 255);
	if (range_check_color(lights->light_color.x)
		|| range_check_color(lights->light_color.y)
		|| range_check_color(lights->light_color.z))
		ratio_error(2);
	lights->next = NULL;
	free_all(origin);
	free_all(color);
	set_light_list(scene, lights);
}
