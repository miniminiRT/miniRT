/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:45:15 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/20 16:13:01 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	get_root(t_util *util, t_hit_record *rec)
{
	util->discriminant = (util->b * util->b) - 4 * util->a * util->c;
	if (util->discriminant < EPSILON)
		return (0);
	util->sqrtd = sqrt(util->discriminant);
	util->root = (-util->b - util->sqrtd) / (2 * util->a);
	if (util->root < rec->tmin || util->root > rec->tmax)
	{
		util->root = (-util->b + util->sqrtd) / (2 * util->a);
		if (util->root < rec->tmin || util->root > rec->tmax)
			return (0);
	}
	return (1);
}

void	get_src_for_disciminant(t_util	*util, t_ray ray, t_cylinder *cy)
{
	t_vec	w;

	w = vec_sub(ray.origin, cy->base_center);
	util->a = vec_dot(ray.dir, ray.dir) \
		- (vec_dot(ray.dir, cy->h) * vec_dot(ray.dir, cy->h));
	util->b = vec_dot(ray.dir, w) - vec_dot(ray.dir, cy->h) * vec_dot(w, cy->h);
	util->b *= 2;
	util->c = vec_dot(w, w) \
		- (vec_dot(w, cy->h) * vec_dot(w, cy->h)) - (cy->radius * cy->radius);
}
