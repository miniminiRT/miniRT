/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:21:06 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/20 12:30:22 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	rgb_to_color(t_vec color)
{
	return ((int)(255.999 * color.x) << 16
		| (int)(255.999 * color.y) << 8
			| (int)(255.999 * color.z));
}

t_vec	get_lower_left_corner(t_scene *scene, \
	t_vec horizontal, t_vec vertical, t_vec w)
{
	t_vec	lower_left_corner;

	lower_left_corner = \
		vec(scene->camera.origin.x + (-horizontal.x / 2) \
		+ (-vertical.x / 2) - (scene->viewport.focal_length * w.x), \
		scene->camera.origin.y + (-horizontal.y / 2) \
		+ (-vertical.y / 2) - (scene->viewport.focal_length * w.y), \
		scene->camera.origin.z + (-horizontal.z / 2) \
		+ (-vertical.z / 2) - (scene->viewport.focal_length * w.z));
	return (lower_left_corner);
}

t_vec	get_ray_dir(t_print p, t_ray ray)
{
	t_vec	dir;

	dir = \
		vec(p.lower_left_corner.x \
		+ p.u * p.horizontal.x + p.v * p.vertical.x - ray.origin.x,
			p.lower_left_corner.y \
		+ p.u * p.horizontal.y + p.v * p.vertical.y - ray.origin.y,
			p.lower_left_corner.z \
		+ p.u * p.horizontal.z + p.v * p.vertical.z - ray.origin.z);
	return (dir);
}

void	set_viewport_vector(t_set_viewport *sv, t_scene *scene)
{
	sv->lookfrom = scene->camera.origin;
	sv->lookat = vec_add(sv->lookfrom, vec_unit(scene->camera.dir));
	sv->vup = vec(0, 1, 0);
	scene->viewport.focal_length = \
		vec_length(vec_sub(sv->lookfrom, sv->lookat));
	sv->w = vec_unit(vec_sub(sv->lookfrom, sv->lookat));
	sv->u = vec_unit(vec_cross(sv->vup, sv->w));
	sv->v = vec_cross(sv->w, sv->u);
}

void	set_print_vector(t_scene *scene, t_print *print_vec, t_set_viewport sv)
{
	print_vec->vertical = vec_mul(sv.v, -scene->viewport.height);
	print_vec->horizontal = vec_mul(sv.u, scene->viewport.width);
	print_vec->lower_left_corner
		= get_lower_left_corner(scene,
			print_vec->horizontal, print_vec->vertical, sv.w);
}
