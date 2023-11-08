/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:10:01 by jonhan            #+#    #+#             */
/*   Updated: 2023/11/02 16:22:28 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	hit(t_scene *scene, t_ray r, t_hit_record *rec, int id)
{
	int				hit_anything;
	t_hit_record	tmp_rec;

	tmp_rec = *rec;
	hit_anything = 0;
	t_object *iter = scene->objects;
	while (iter)
	{
		if (iter->id != id)
		{
			if (hit_sphere(rec, r, iter->element))
			{
				hit_anything = 1;
				tmp_rec.tmax = tmp_rec.t;
				*rec = tmp_rec;
			}
			// 평면 추가하기
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
	if (hit(scene, r, &rec, id))
		// return (1);
		return (0);
	return (0);
}
