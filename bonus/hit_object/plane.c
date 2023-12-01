/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 14:07:47 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/20 14:07:47 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	hit_plane(t_hit_record *rec, t_ray ray, t_plane *pl)
{
	double	denom;
	double	t;

	denom = vec_dot(pl->normal, vec_mul(ray.dir, -1));
	if (denom > EPSILON)
	{
		t = vec_dot(pl->point, pl->normal) - vec_dot(pl->normal, ray.origin);
		t /= vec_dot(pl->normal, ray.dir);
		if (t > 0)
		{
			if (t < rec->tmin || t > rec->tmax)
			{
				return (0);
			}
			rec->tmax = t;
			rec->t = t;
			rec->p = ray_at(ray, rec->t);
			rec->albedo = pl->color;
			rec->normal = pl->normal;
			return (1);
		}
	}
	return (0);
}
