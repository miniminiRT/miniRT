#include "miniRT.h"

t_vec	set_face_normal(t_vec normal, t_ray ray)
{
	if (vec_dot(ray.dir, normal) > 0.0)
		return (vec(-normal.x, -normal.y, -normal.z));
	return (normal);
}

int rgb_to_color(t_vec color)
{
	return ((int)(255.999 * color.x) << 16
		| (int)(255.999 * color.y) << 8
			| (int)(255.999 * color.z));
}

int check_is_hit(t_ray ray, t_scene *scene, t_object *obj)
{
	int is_hit;

	is_hit = 0;
	if (obj->type == SPHERE)
		is_hit = hit_sphere(&(scene->rec), ray, obj->element);
	else if (obj->type == PLANE)
		is_hit = hit_plane(&(scene->rec), ray, obj->element);
	else if (obj->type == CYLINDER)
		is_hit = hit_cylinder(&(scene->rec), ray, obj->element);
	return (is_hit);
}

int ray_color(t_ray ray, t_scene *scene)
{
	int             tmp_id;
	double          rec_tmp;
	t_vec           color;
	t_object        *obj_list;

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
	color = phong_light(scene, tmp_id);
	return (rgb_to_color(color));
}

t_vec   get_lower_left_corner(t_scene *scene, t_vec horizontal, t_vec vertical, t_vec w)
{
	t_vec   lower_left_corner;

	lower_left_corner =
		vec(scene->camera.origin.x + (- horizontal.x / 2) \
		+ (-vertical.x / 2) - (scene->viewport.focal_length * w.x), \
		scene->camera.origin.y + (- horizontal.y / 2) \
		+ (- vertical.y / 2) - (scene->viewport.focal_length * w.y), \
		scene->camera.origin.z + (- horizontal.z / 2) \
		+ (-vertical.z / 2) - (scene->viewport.focal_length * w.z));
	return (lower_left_corner);
}

t_vec   get_ray_dir(t_print p, t_ray ray)
{
	t_vec   dir;

	dir =
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
	scene->viewport.focal_length = vec_length(vec_sub(sv->lookfrom, sv->lookat));
	sv->w = vec_unit(vec_sub(sv->lookfrom, sv->lookat));
	sv->u = vec_unit(vec_cross(sv->vup, sv->w));
	sv->v = vec_cross(sv->w, sv->u);
}

void	set_print_vector(t_scene *scene, t_print *print_vec, t_set_viewport sv)
{
	print_vec->vertical = vec_mul(sv.v, -scene->viewport.height);
	print_vec->horizontal = vec_mul(sv.u, scene->viewport.width);
	print_vec->lower_left_corner
		= get_lower_left_corner(scene, print_vec->horizontal, print_vec->vertical, sv.w);
}

void print_scene(t_scene *scene, t_data image)
{
	int		i;
	int		j;
	t_ray	ray;
	t_print print_vec;
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
