/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:10:01 by jonhan            #+#    #+#             */
/*   Updated: 2023/11/18 15:04:53 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	hit(t_scene *scene, t_ray r, t_hit_record rec, int id)
{
	int				hit_anything;
	t_hit_record	tmp_rec;
	t_object		*iter;

	hit_anything = 0;
	tmp_rec = rec;
	iter = scene->objects;
	while (iter)
	{
		if (iter->id != id)
		{
			if (iter->type == SPHERE)
			{
				hit_anything = hit_sphere(&rec, r, iter->element);
			}
			else if (iter->type == CYLINDER)
			{
				hit_anything = hit_cylinder(&rec, r, iter->element);
			}
			else if (iter->type == PLANE)
			{
				hit_anything = hit_plane(&rec, r, iter->element);
			}
			if (hit_anything == 1)
				return (1);
		}
		iter = iter->next;
	}
	return (hit_anything);
}

int	in_shadow(t_scene *scene, t_ray r, double light_len, int id)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(scene, r, rec, id))
		return (1);
	return (0);
}
