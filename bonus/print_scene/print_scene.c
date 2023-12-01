/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:20:24 by seojchoi          #+#    #+#             */
/*   Updated: 2023/12/01 14:57:54 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"
#define WIDTH 1000
#define HEIGHT 562

int	check_is_hit(t_ray ray, t_scene *scene, t_object *obj)
{
	int	is_hit;

	is_hit = 0;
	if (obj->type == SPHERE)
		is_hit = hit_sphere(&(scene->rec), ray, obj->element);
	else if (obj->type == PLANE)
		is_hit = hit_plane(&(scene->rec), ray, obj->element);
	else if (obj->type == CYLINDER)
		is_hit = hit_cylinder(&(scene->rec), ray, obj->element);
	return (is_hit);
}

int	ray_color(t_ray ray, t_scene *scene)
{
	int			tmp_id;
	double		rec_tmp;
	t_vec		color;
	t_object	*obj_list;

	tmp_id = -1;
	rec_tmp = INFINITY;
	scene->rec.tmin = 0;
	scene->rec.tmax = INFINITY;
	obj_list = scene->objects;
	while (obj_list)
	{
		if (check_is_hit(ray, scene, obj_list))
		{
			if (scene->rec.t < rec_tmp)
			{
				rec_tmp = scene->rec.t;
				tmp_id = obj_list->id;
			}
		}
		obj_list = obj_list->next;
	}
	color = phong_light(scene, tmp_id, 0);
	return (rgb_to_color(color));
}

t_vec	screen2view(t_camera *cam, int x, int y, t_set_viewport *sv)
{
	t_vec	exchange_point;

	cam->ratio = WIDTH / HEIGHT;
	cam->x_axis = vec_mul(sv->u, cam->fov * 2.0 * cam->ratio);
	cam->y_axis = vec_mul(sv->v, cam->fov * 2.0);
	cam->left_top = vec_add(vec_mul(cam->x_axis, -0.5), \
		vec_mul(cam->y_axis, 0.5));
	cam->left_top = vec_add(sv->w, cam->left_top);
	cam->change_x = vec_div(cam->x_axis, WIDTH);
	cam->change_y = vec_div(cam->y_axis, HEIGHT);
	exchange_point = vec_add(cam->left_top, vec_mul(cam->change_x, x));
	exchange_point = vec_add(exchange_point, vec_mul(cam->change_y, -1 * y));
	return (exchange_point);
}

void	print_scene(t_scene *scene, t_data image)
{
	int				i;
	int				j;
	t_ray			ray;
	t_print			print_vec;
	t_set_viewport	sv;

	set_viewport_vector(&sv, scene);
	set_print_vector(scene, &print_vec, sv);
	ray.origin = scene->camera.origin;
	j = scene->size.height;
	while (--j >= 0)
	{
		i = -1;
		while (++i < scene->size.width)
		{
			print_vec.u = (double)i / (scene->size.width - 1);
			print_vec.v = (double)j / (scene->size.height - 1);
			ray.dir = get_ray_dir(print_vec, ray);
			scene->ray = ray;
			my_mlx(&image, i, j, ray_color(ray, scene));
		}
	}
}
