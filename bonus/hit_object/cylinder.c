/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:33:03 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/20 16:12:47 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
#define SIDE 1
#define TOP 2
#define BASE 3

int	set_cylinder_rec(t_hit_record *rec, t_ray ray, t_cylinder *cy, int type)
{
	t_vec	cp;
	t_vec	qp;

	rec->p = ray_at(ray, rec->t);
	rec->albedo = cy->color;
	if (type == SIDE)
	{
		cp = vec_sub(rec->p, cy->base_center);
		qp = vec_sub(cp, vec_mul(cy->h, vec_dot(cp, cy->h)));
		rec->normal = vec_unit(qp);
	}
	else
		rec->normal = vec_unit(cy->normal);
	rec->normal = set_face_normal(rec->normal, ray);
	return (1);
}

int	is_base(t_hit_record *rec, t_ray ray, t_cylinder *cy, t_vec center)
{
	double	denom;
	double	t;
	double	s;
	t_vec	n;

	n = vec_mul(cy->normal, -1);
	denom = vec_dot(n, vec_mul(ray.dir, -1));
	if (denom > EPSILON)
	{
		t = vec_dot(center, n) - vec_dot(n, ray.origin);
		t /= vec_dot(n, ray.dir);
		if (t > 0)
		{
			if (t < rec->tmin || t > rec->tmax)
				return (0);
			s = vec_length(vec_sub(ray_at(ray, t), center));
			if (!(s > 0.0 && s <= cy->radius))
				return (0);
			rec->tmax = t;
			rec->t = t;
			return (set_cylinder_rec(rec, ray, cy, BASE));
		}
	}
	return (0);
}

int	is_top(t_hit_record *rec, t_ray ray, t_cylinder *cy, t_vec center)
{
	double	denom;
	double	t;
	double	s;

	denom = vec_dot(cy->normal, vec_mul(ray.dir, -1));
	if (denom > EPSILON)
	{
		t = vec_dot(center, cy->normal) - vec_dot(cy->normal, ray.origin);
		t /= vec_dot(cy->normal, ray.dir);
		if (t > 0)
		{
			if (t < rec->tmin || t > rec->tmax)
				return (0);
			s = vec_length(vec_sub(ray_at(ray, t), center));
			if (!(s >= 0.0 && s <= cy->radius))
				return (0);
			rec->tmax = t;
			rec->t = t;
			return (set_cylinder_rec(rec, ray, cy, TOP));
		}
	}
	return (0);
}

void	get_top_base_center(t_cylinder *cy)
{
	t_ray	up;
	t_ray	down;

	up.dir = vec_unit(cy->normal);
	up.origin = cy->center;
	up.t = cy->height / 2;
	cy->top_center = ray_at(up, up.t);
	down.dir = vec_unit(vec_mul(cy->normal, -1));
	down.origin = cy->center;
	down.t = cy->height / 2;
	cy->base_center = ray_at(down, down.t);
	cy->h = vec_div(vec_sub(cy->top_center, cy->base_center), cy->height);
}

int	hit_cylinder(t_hit_record *rec, t_ray ray, t_cylinder *cy)
{
	t_util	util;
	double	size;

	get_top_base_center(cy);
	get_src_for_disciminant(&util, ray, cy);
	if (get_root(&util, rec) == 0)
		return (0);
	size = vec_dot(vec_sub(ray_at(ray, util.root), cy->base_center), cy->h);
	if (size < 0.0)
		return (is_base(rec, ray, cy, cy->base_center));
	if (size > cy->height)
		return (is_top(rec, ray, cy, cy->top_center));
	if (size >= 0 && size <= cy->height)
	{
		rec->tmax = util.root;
		rec->t = util.root;
		return (set_cylinder_rec(rec, ray, cy, SIDE));
	}
	return (0);
}
