/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:02:41 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/28 16:33:42 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define LUMEN 3
#define KA 0.1
#define EPSILON 1e-6

t_vec	reflect(t_vec v, t_vec n)
{
	t_vec	light_y_dir;
	t_vec	result;

	light_y_dir = vec_mul(n, vec_dot(v, n) * 2);
	result = vec_sub(v, light_y_dir);
	// 공식이 왜 이렇게 되는지 이해 안됨.
	return (result);
}

t_vec	point_light_get(t_scene *scene, t_light *light, int id)
{
	t_phong	arg;

	arg.light_dir = vec_sub(light->origin, scene->rec.p);
	arg.light_len = vec_length(arg.light_dir);
	arg.light_ray = ray(vec_add(scene->rec.p, \
		vec_mul(scene->rec.normal, EPSILON)), arg.light_dir);
	if (in_shadow(scene, arg.light_ray, arg.light_len, id))
		return (vec(0, 0, 0));
	arg.light_dir = vec_unit(arg.light_dir);
	arg.kd = fmax(vec_dot(scene->rec.normal, arg.light_dir), 0.0);
	arg.diffuse = vec_mul(light->light_color, arg.kd);
	arg.view_dir = vec_unit(vec_mul(scene->ray.dir, -1));
	arg.reflect_dir = reflect(vec_mul(arg.light_dir, -1), scene->rec.normal);
	arg.ksn = 64;
	arg.ks = 0.5;
	arg.spec = pow(fmax(vec_dot(arg.view_dir, arg.reflect_dir), 0.0), arg.ksn);
	arg.specular = vec_mul(vec_mul(light->light_color, arg.ks), arg.spec);
	arg.brightness = light->brightness * LUMEN;
	arg.light_sum = vec_add(arg.diffuse, arg.specular);
	return (vec_mul(arg.light_sum, arg.brightness));
}


t_vec	phong_light(t_scene	*scene, int id)
{
	t_vec	light_color;
	t_vec	light_sum;

	light_color = vec(0, 0, 0);
	while (scene->lights)
	{
		light_color = \
			vec_add(light_color, point_light_get(scene, scene->lights, id));
		scene->lights = scene->lights->next;
	}
	light_color = vec_add(light_color, scene->ambient.color);
	light_sum = vec_mul_vec(light_color, scene->rec.albedo);
	return (vec_min(light_sum, vec(1, 1, 1)));
}
