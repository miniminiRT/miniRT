#include "miniRT.h"

#define ka 0.1

t_vec	set_face_normal(t_vec normal, t_ray ray)
{
	if (vec_dot(ray.dir, normal) > 0.0)
	{
        // 내각한 결과가 양수이면 카메라가 구의 안쪽에 있다는 뜻. 법선벡터의 방향 바꿔주기
		return (vec(-normal.x, -normal.y, -normal.z));
	}
	return (normal);  // 카메라가 구의 바깥에 있으면 그대로 리턴하기
}

int rgb_to_color(t_vec color)
{
    return ((int)(255.999 * color.x) << 16
        | (int)(255.999 * color.y) << 8
            | (int)(255.999 * color.z));
}

int ray_color(t_ray ray, t_scene *scene)
{
    int             is_hit;
    t_vec           color;
	t_object        *obj_list;

	color = vec(0, 0, 0);    // color값 초기화
	scene->rec.tmin = 0;
	scene->rec.tmax = INFINITY;
	double rec_tmp = INFINITY;
	int    tmp_id = -1;
	scene->ambient.color = vec_mul(scene->ambient.color, ka);
	obj_list = scene->objects;
	while (obj_list)
	{
		is_hit = 0;
		if (obj_list->type == SPHERE)
			is_hit = hit_sphere(&(scene->rec), ray, obj_list->element);
		else if (obj_list->type == PLANE)
			is_hit = hit_plane(&(scene->rec), ray, obj_list->element);
		else if (obj_list->type == CYLINDER)
			is_hit = hit_cylinder(&(scene->rec), ray, obj_list->element);
		if (is_hit == 1)
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
        vec(scene->camera.origin.x + (- horizontal.x / 2) + (-vertical.x / 2) - (scene->viewport.focal_length * w.x),
        scene->camera.origin.y + (- horizontal.y / 2) + (- vertical.y / 2) - (scene->viewport.focal_length * w.y),
        scene->camera.origin.z + (- horizontal.z / 2) + (-vertical.z / 2) - (scene->viewport.focal_length * w.z));
    return (lower_left_corner);
}

t_vec   get_ray_dir(t_print p, t_ray ray)
{
    t_vec   dir;

    dir = 
        vec(p.lower_left_corner.x + p.u * p.horizontal.x + p.v * p.vertical.x - ray.origin.x,
        p.lower_left_corner.y + p.u * p.horizontal.y + p.v * p.vertical.y - ray.origin.y,
        p.lower_left_corner.z + p.u * p.horizontal.z + p.v * p.vertical.z - ray.origin.z);
    return (dir);
}

void print_scene(t_scene *scene, t_data image)
{
    int     i;
    int     j;
    t_ray   ray;
    t_print print_vec;

    // camera view 추가
    t_vec   lookfrom = scene->camera.origin;
    t_vec   lookat = vec_add(lookfrom, vec_unit(scene->camera.dir));
    t_vec   vup = vec(0, 1, 0);
    scene->viewport.focal_length = vec_length(vec_sub(lookfrom, lookat));
    t_vec   w = vec_unit(vec_sub(lookfrom, lookat));  // 시선 방향 벡터
    t_vec   u = vec_unit(vec_cross(vup, w));  // 카메라 좌우 방향 벡터
    t_vec   v = vec_cross(w, u);  // 카메라 상하 방향 벡터

    // lower_left_corner
    print_vec.vertical = vec_mul(v, -scene->viewport.height);
    print_vec.horizontal = vec_mul(u, scene->viewport.width);
    print_vec.lower_left_corner
        = get_lower_left_corner(scene, print_vec.horizontal, print_vec.vertical, w);
    // ray
    ray.origin = scene->camera.origin;   // 카메라에서 나오는 ray
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
