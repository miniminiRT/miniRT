/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 12:02:41 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/24 20:29:45 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define LUMEN 3
#define ka 0.1
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

t_vec	point_light_get(t_scene *scene, t_light *light, t_ray r)
{
	t_vec	diffuse;
	t_vec	light_dir;
	double	kd;
	t_vec	specular;
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	spec;
	double	ksn;
	double	ks;
	double	brightness;
	t_vec	light_sum;
	t_ray	light_ray;
	double	light_len;

	light_dir = vec_sub(light->origin, scene->rec.p);
	light_len = vec_length(light_dir);
	light_ray = ray(vec_add(scene->rec.p, vec_mul(scene->rec.normal, EPSILON)), light_dir);
	if (in_shadow(scene, light_ray, light_len))
		return (vec(0, 0, 0));
	// light_dir = vec_unit(vec_sub(light->origin, scene->rec.p));
	light_dir = vec_unit(light_dir);
	kd = fmax(vec_dot(scene->rec.normal, light_dir), 0.0);
	diffuse = vec_mul(light->light_color, kd);
	view_dir = vec_unit(vec_mul(r.dir, -1));
	reflect_dir = reflect(vec_mul(light_dir, -1), scene->rec.normal);
	ksn = 64;
	ks = 0.5;
	t_vec ambient = vec_mul(scene->ambient.color, 0.1);
	spec = pow(fmax(vec_dot(view_dir, reflect_dir), 0.0), ksn);
	specular = vec_mul(vec_mul(light->light_color, ks), spec);
	brightness = light->brightness * LUMEN;
	brightness = 1.5;
	light_sum = vec_add(vec_add(ambient, diffuse), specular);
	printf("%f %f %f\n", light_sum.x, light_sum.y, light_sum.z);
	return (vec_mul(light_sum, brightness));
}


t_vec	phong_light(t_scene	*scene, t_ray ray)
{
	t_vec	light_color;
	t_vec	light_sum;

	light_color = vec(1, 1, 1);
	while (scene->lights)
	{
		light_color = vec_add(light_color, point_light_get(scene, scene->lights, ray));
		scene->lights = scene->lights->next;
	}
	t_vec ambient = vec_mul(scene->ambient.color, 0.1);
		// printf("%f %f %f\n", light_color.x, light_color.y, light_color.z);
	light_color = vec_add(light_color, ambient);
	light_sum = vec_mul_vec(light_color, scene->rec.albedo);
	// light_sum = vec_mul_vec(light_color, vec(0, 0.5, 0));
	return (vec_min(light_sum, vec(1, 1, 1)));
}
