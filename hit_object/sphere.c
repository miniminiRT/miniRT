/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:09:11 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/20 16:01:55 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	set_sphere_rec(t_hit_record *rec, t_sphere *sp, t_ray ray, double root)
{
	t_vec	normal;

	rec->albedo = sp->albedo;
	rec->t = root;
	rec->tmax = rec->t;
	rec->p = ray_at(ray, rec->t);
	normal = vec_div((vec_sub(rec->p, sp->center)), sp->radius);
	rec->normal = set_face_normal(normal, ray);
}

int	hit_sphere(t_hit_record *rec, t_ray ray, t_sphere *sp)
{
	t_vec	oc;
	t_util	util;

	oc = vec_sub(ray.origin, sp->center);
	util.a = vec_dot(ray.dir, ray.dir);
	util.b = 2.0 * vec_dot(oc, ray.dir);
	util.c = vec_dot(oc, oc) - (sp->radius * sp->radius);
	if (get_root(&util, rec) == 0)
		return (0);
	set_sphere_rec(rec, sp, ray, util.root);
	return (1);
}
