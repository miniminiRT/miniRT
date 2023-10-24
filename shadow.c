/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:10:01 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/24 14:45:24 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	hit(t_scene *scene, t_ray r, t_hit_record *rec)
{
	int				hit_anything;
	t_hit_record	tmp_rec;

	tmp_rec = *rec;
	hit_anything = 0;
	while (scene->objects)
	{
		if (hit_sphere(rec, r, scene->objects->element))
		{
			hit_anything = 1;
			tmp_rec.tmax = tmp_rec.t;
			*rec = tmp_rec;
		}
		scene->objects = scene->objects->next;
	}
	return (hit_anything);
}

int	in_shadow(t_scene *scene, t_ray r, double light_len)
{
	t_hit_record	rec;

	rec.tmin = 0;
	rec.tmax = light_len;
	if (hit(scene, r, &rec))
		return (1);
	return (0);
}
