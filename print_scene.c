#include "miniRT.h"

t_vec	set_face_normal(t_vec normal, t_ray ray)
{
	if (vec_dot(ray.dir, normal) > 0.0)
	{
		return (vec(-normal.x, -normal.y, -normal.z));  // 내각한 결과가 양수이면 카메라가 구의 안쪽에 있다는 뜻. 법선벡터의 방향 바꿔주기
	}
	return (normal);  // 카메라가 구의 바깥에 있으면 그대로 리턴하기
}

void    set_rec(t_hit_record *rec, t_sphere *sp, t_ray ray, double root)
{
    t_vec   normal;

    rec->albedo = sp->albedo;
	rec->t = root;
    rec->tmax = rec->t;
	rec->p = ray_at(ray, rec->t);
	// 법선 벡터의 방향을 계산해서 써줘야 함.
	normal = vec_div((vec_sub(rec->p, sp->center)), sp->radius);
	rec->normal = set_face_normal(normal, ray);  // 안, 밖 고려해서 법선벡터 바꾸기
}

int hit_sphere(t_hit_record *rec, t_ray ray, t_sphere *sp)
{
    double  root;
    double  discriminant;
    t_util  util;

    util.oc = vec_sub(ray.origin, sp->center);
    util.a = vec_dot(ray.dir, ray.dir);
    util.b = 2.0 * vec_dot(util.oc, ray.dir);
    util.c = vec_dot(util.oc, util.oc) - (sp->radius * sp->radius);
    discriminant = (util.b * util.b) - 4 * (util.a * util.c);
	if (discriminant < 0)  // 판별식이 음수이면 해가 없음.
		return (0);
    util.sqrtd = sqrt(discriminant);
    root = (-util.b - util.sqrtd) / (2 * util.a);
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-util.b + util.sqrtd) / (2 * util.a);
		if (root < rec->tmin || root > rec->tmax)
			return (0);
	}
    set_rec(rec, sp, ray, root);
	// rec->albedo = sp->albedo;
	// rec->t = root;
    // rec->tmax = rec->t;
	// rec->p = ray_at(ray, rec->t);
	// // 법선 벡터의 방향을 계산해서 써줘야 함.
	// normal = vec_div((vec_sub(rec->p, sp->center)), sp->radius);
	// rec->normal = set_face_normal(normal, ray);  // 안, 밖 고려해서 법선벡터 바꾸기
	return (1);
}

int rgb_to_color(t_vec color)
{
    return ((int)(255.999 * color.x) << 16
        | (int)(255.999 * color.y) << 8
            | (int)(255.999 * color.z));
}

int ray_color(t_ray ray, t_scene scene)
{
    int             is_hit;
    t_vec           color;
    t_object        *obj_list;

    color = vec(0, 0, 0);    // color값 초기화
    scene.rec.tmin = 0;
    scene.rec.tmax = INFINITY;
    scene.ambient.color = vec_mul(scene.ambient.color, 0.1);   // define ka : 0.1
    obj_list = scene.objects;
    while (obj_list)
    {
        is_hit = 0;
        if (obj_list->type == SPHERE)
            is_hit = hit_sphere(&(scene.rec), ray, obj_list->element);
        if (is_hit == 1)
        {
            color = phong_light(&scene, obj_list->id);
        }
        obj_list = obj_list->next;
    }
    return (rgb_to_color(color));
}

t_vec   get_lower_left_corner(t_scene scene, t_vec horizontal, t_vec vertical)
{
    t_vec   lower_left_corner;

    lower_left_corner = 
        vec(scene.camera.origin.x + (- horizontal.x / 2) + (-vertical.x / 2) + (0),
        scene.camera.origin.y + (- horizontal.y / 2) + (- vertical.y / 2) + (0),
        scene.camera.origin.z + (- horizontal.z / 2) + (-vertical.z / 2) + (-scene.viewport.focal_length));
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

void print_scene(t_scene scene, t_data image)
{
    int     i;
    int     j;
    t_ray   ray;
    t_print print_vec;

    // lower_left_corner
    print_vec.vertical = vec(0, -scene.viewport.height, 0);
    print_vec.horizontal = vec(scene.viewport.width, 0, 0);
    print_vec.lower_left_corner
        = get_lower_left_corner(scene, print_vec.horizontal, print_vec.vertical);
    // ray
    ray.origin = scene.camera.origin;   // 카메라에서 나오는 ray
    j = scene.size.height;
    while (--j >= 0)
    {
        i = -1;
        while (++i < scene.size.width)
        {
            print_vec.u = (double)i / (scene.size.width - 1);
			print_vec.v = (double)j / (scene.size.height - 1);
            ray.dir = get_ray_dir(print_vec, ray);
            scene.ray = ray;
			my_mlx(&image, i, j, ray_color(ray, scene));
        }
    }
}
