/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   back.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:04:49 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/22 13:17:12 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

// https://github.com/GaepoMorningEagles/mini_raytracing_in_c/blob/main/08.phong_lighting.md
#define ka 0.1
#define LUMEN 3

t_light	*light_point(t_vec3 light_origin, t_vec3 light_color, double bright_ratio)
{
	t_light	*light;

	light = (t_light *)malloc(sizeof(t_light));
	light->origin = light_origin;
	light->light_color = light_color;
	light->bright_ratio = bright_ratio;
	return (light);
}

// t_vec3	phong_lighting(t_light *light)
// {
// 	t_vec3	light_color;
// 	t_light	*lights;

// 	light_color = vec3_create(0,0,0);
// 	lights = light;
// }

t_ray	ray_create(t_vec3 origin, t_vec3 vertical, t_vec3 horizontal, t_vec3 lower_left_corner)
{
    t_ray r;

	r.origin = vec3_create(0, 0, 0);
	r.dir = vec3_create(lower_left_corner.e[0] + horizontal.e[0] + vertical.e[0] - origin.e[0],
			lower_left_corner.e[1] + horizontal.e[1] + vertical.e[1] - origin.e[1],
			lower_left_corner.e[2] + horizontal.e[2] + vertical.e[2] - origin.e[2]);
	return (r);
}

t_vec3	ray_at(double t, t_vec3 origin, t_vec3 direction)
{
	t_vec3 scaled_direction = multiply_vec3_scalar(direction, t);
	t_vec3 result = vec3_add(origin, scaled_direction);
	return (result);
}

void	set_face_normal(t_ray r, t_vec3 *outward_normal, t_hit_record *rec)
{
	if (dot_product(&r.dir, outward_normal) > 0.0)
	{
		rec->normal = vec3_negate(*outward_normal);
		rec->front_face = 0;
	}
	else
	{
		rec->normal = *outward_normal;
		rec->front_face = 1;
	}
	return ;
}

double	hit_sphere(t_ray r, double t_max, double t_min, t_hit_record *rec, t_sphere *sphere)
{
	t_vec3 oc = vec3_add(r.origin, vec3_negate(sphere->center));
	double a = dot_product(&(r.dir), &(r.dir));
	double half_b = dot_product(&oc, &(r.dir));
	double c = dot_product(&oc, &oc) - sphere->radius * sphere->radius;
	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	double sqrtd = sqrt(discriminant);
	double root = ((-half_b) - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = ((-half_b) + sqrtd) / a;
		if (root < t_min || t_max < root)
			return 0;
	}
	rec->t = root;
	rec->point = ray_at(rec->t, r.origin, r.dir);
	rec->normal = vec3_divide(vec3_add(rec->point, vec3_negate(sphere->center)), sphere->radius);
	rec->albedo = sphere->albedo;
	set_face_normal(r, &(rec->normal), rec);
	return (1);
}


void	my_mlx(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

t_sphere *sphere(t_vec3 center,double radius, t_vec3 albedo)
{
	t_sphere *sp;
	sp = malloc(sizeof(t_sphere) * 1);
	sp->center = center;
	sp->radius = radius;
	sp->albedo = albedo;
	sp->next = NULL;
	return (sp);
}

t_vec3	reflect(t_vec3 v, t_vec3 n)
{
	return (vec3_minus(v, multiply_vec3_scalar(n, dot_product(&v, &n) * 2)));
}

t_vec3	point_light_get(t_hit_record rec, t_light *light, t_ray r, t_vec3 ambient)
{
	t_vec3 diffuse;
	t_vec3 light_dir;
	double kd;
	//***************
	t_vec3 specular;
	t_vec3 view_dir;
	t_vec3 reflect_dir;
	double spec;
	double ksn;
	double ks;
	double brightness;
	
	light_dir = vec3_unit(vec3_minus(light->origin, rec.point));
	kd = fmax(dot_product(&rec.normal, &light_dir), 0.0);
	diffuse = multiply_vec3_scalar(light->light_color, kd);

	view_dir = vec3_unit(vec3_negate(r.dir));
	reflect_dir = reflect(vec3_negate(light_dir), rec.normal);
	ksn = 64;
	ks = 0.5;
	spec = pow(fmax(dot_product(&view_dir, &reflect_dir), 0.0), ksn);
	specular = multiply_vec3_scalar(multiply_vec3_scalar(light->light_color, ks), spec);
	brightness = light->bright_ratio * LUMEN;

	return (multiply_vec3_scalar(vec3_add(vec3_add(ambient, diffuse), specular), brightness));
}

t_vec3 phong_lighting(t_hit_record rec, t_sphere *sphere, t_ray r)
{
	t_vec3	light_color;
	t_light	*lights;
	t_vec3	ambient;

	ambient = multiply_vec3_scalar(vec3_create(1,1,1), ka);
	lights = light_point(vec3_create(0,5,0),vec3_create(1,1,1), 0.5);
	light_color = vec3_create(0, 0, 0);
	if (lights)
	{
		light_color = vec3_add(light_color, point_light_get(rec, lights, r, ambient));
	}
	light_color = vec3_add(light_color, ambient);
	return (vmin(vec3_multiply_vec3(light_color, rec.albedo), vec3_create(1,1,1)));
	//모든 광원에 의한 빛의 양을 구한 후, 오브젝트의 반사율과 곱해준다. 그 값이 (1,1,1)넘으면 1,1,1리턴
}

t_vec3 ray_color(t_ray r)
{
	t_vec3	tmp;
	t_vec3	N;
	t_vec3 color;
	double	t;
	t_sphere	*sphere1;
	t_sphere	*sphere2;
	t_sphere	*sphere3;
	t_hit_record rec;
	int			flag;

	flag = 0;
	sphere1 = sphere(vec3_create(2, 0, -5), 2, vec3_create(0, 0.8, 0.9));
	sphere2 = sphere(vec3_create(-2, 0, -5), 2, vec3_create(0.2, 0.5, 0.2));
	sphere3 = sphere(vec3_create(0, -1001, 0),999, vec3_create(1, 1, 1));
	sphere2->next = sphere3;
	sphere1->next = sphere2;
	rec.t = INFINITY;
	while (sphere1 != NULL)
	{
		t = hit_sphere(r, rec.t, 0, &rec, sphere1);
		if (t > 0.0)
		{
			// tmp = ray_at(rec.t, r.origin, r.dir);
			color = phong_lighting(rec, sphere1, r);
			flag = 1;
			// N = vec3_unit(vec3_create(tmp.e[0] - sphere1->center.e[0], tmp.e[1] - sphere1->center.e[1], tmp.e[2] - sphere1->center.e[2]));  // 현재 구의 중점으로 빼기
			// color = multiply_vec3_scalar(vec3_create(N.e[0] + 1, N.e[1] + 1, N.e[2] + 1), 0.5);
			// color = vec3_create(0 ,1, 0);
		}
		sphere1 = sphere1->next;
	}
	if (flag == 1)
		return (color);
	t_vec3 unit_direction = vec3_unit(r.dir);
	t = 0.5 *(unit_direction.e[1] + 1.0);
	return (vec3_add(multiply_scalar_vec3((1.0 - t), vec3_create(1, 1, 1)), multiply_scalar_vec3(t, vec3_create(0.5, 0.7, 1.0))));
	// color = vec3_create(1.0 - 0.5 * t, 1.0 - 0.3 * t, 1.0);
	// return (color);
	// (1.0 - t)*color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0)
}

void print(t_data image)
{
    double aspect_ratio = 16.0/9.0;
    int image_width = 1600;
    int image_height = (int)((double)image_width / aspect_ratio);

    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    t_vec3 origin = vec3_create(0,0,0);
    t_vec3 vertical = vec3_create(0, -viewport_height ,0);
    t_vec3 horizontal = vec3_create(viewport_width, 0, 0);

    // 지금은 원점이 0,0,0이니까 이거 쓰자
    t_vec3 lower_left_corner = 
	vec3_create(origin.e[0] + (- horizontal.e[0] / 2) + (-vertical.e[0] / 2) + (0)
		 ,origin.e[1] + (- horizontal.e[1] / 2) + (-vertical.e[1] / 2) + (0) 
		 ,origin.e[2] + (- horizontal.e[2] / 2) + (-vertical.e[2] / 2) + (-focal_length));

    // t_vec3 lower_left_corner = vec3_add(vec3_add(origin, vec3_negate(vec3_divide(horizontal, 2))),
    //         vec3_add(vec3_divide(vertical, 2), vec3_negate(vec3_create(0, 0, focal_length))));

	for (int j = image_height - 1; j >= 0; --j) {
		for (int i = 0; i < image_width; ++i) {
			double u = (double)(i) / (image_width-1);
			double v = (double)(j) / (image_height-1);
			
			t_ray r = ray_create(origin, multiply_vec3_scalar(vertical, v),multiply_vec3_scalar(horizontal, u), lower_left_corner);
			t_vec3 vec = ray_color(r);

			int ir = (int)(255.999 * vec.e[0]);
			int ig = (int)(255.999 * vec.e[1]);
			int ib = (int)(255.999 * vec.e[2]);
			int rgbValue = (ir << 16) | (ig << 8) | ib;
			my_mlx(&image, i, j, rgbValue);
		}
	}
}

int	main(void)
{
	t_vars	vars;
	t_data	image;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1600, 900, "");
	image.img = mlx_new_image(vars.mlx, 1600, 900);
	image.addr = mlx_get_data_addr(image.img, &image.bits_per_pixel,
			&image.line_length, &image.endian);
	print(image);
	mlx_put_image_to_window(vars.mlx, vars.win, image.img, 0, 0);
	mlx_loop(vars.mlx);
}
