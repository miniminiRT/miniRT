/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operator3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:21:36 by jonhan            #+#    #+#             */
/*   Updated: 2023/11/20 15:15:54 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	vec_mul_vec(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vec	vec_min(t_vec v1, t_vec v2)
{
	t_vec	new;

	if (v1.x < v2.x)
		new.x = v1.x;
	else
		new.x = v2.x;
	if (v1.y < v2.y)
		new.y = v1.y;
	else
		new.y = v2.y;
	if (v1.z < v2.z)
		new.z = v1.z;
	else
		new.z = v2.z;
	return (new);
}

t_vec	ray_at(t_ray ray, double t)
{
	t_vec	out;

	out.x = ray.origin.x + ray.dir.x * t;
	out.y = ray.origin.y + ray.dir.y * t;
	out.z = ray.origin.z + ray.dir.z * t;
	return (out);
}

t_ray	ray(t_vec origin, t_vec dir)
{
	t_ray	r;

	r.origin = origin;
	r.dir = dir;
	return (r);
}
