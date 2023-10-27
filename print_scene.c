#include "miniRT.h"

t_vec	set_face_normal(t_vec normal, t_ray ray)
{
	if (vec_dot(ray.dir, normal) > 0.0)
	{
		return (vec(-normal.x, -normal.y, -normal.z));  // 내각한 결과가 양수이면 카메라가 구의 안쪽에 있다는 뜻. 법선벡터의 방향 바꿔주기
	}
	return (normal);  // 카메라가 구의 바깥에 있으면 그대로 리턴하기
}

int hit_sphere(t_hit_record *rec, t_ray ray, t_sphere *sp)
{
    double  a;
    double  b;
    double  c;
    double	discriminant;
    double  sqrtd;
    double  root;
    t_vec   oc;
    t_vec   normal;

    oc = vec_sub(ray.origin, sp->center);
    a = vec_dot(ray.dir, ray.dir);
    b = 2.0 * vec_dot(oc, ray.dir);
    c = vec_dot(oc, oc) - (sp->radius * sp->radius);
    discriminant = b * b - 4 * a * c;
	if (discriminant < 0)  // 판별식이 음수이면 해가 없음.
		return (0);
    sqrtd = sqrt(discriminant);
    root = (-b - sqrtd) / (2 * a);
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-b + sqrtd) / (2 * a);
		if (root < rec->tmin || root > rec->tmax)
			return (0);
	}
	rec->albedo = sp->albedo;
	rec->t = root;
    rec->tmax = rec->t;
	rec->p = ray_at(ray, rec->t);
	// 법선 벡터의 방향을 계산해서 써줘야 함.
	normal = vec_div((vec_sub(rec->p, sp->center)), sp->radius);
	rec->normal = set_face_normal(normal, ray);  // 안, 밖 고려해서 법선벡터 바꾸기
	return (1);
}

int ray_color(t_ray ray, t_scene scene)
{
    int             is_hit;
    t_vec           color;
    t_object        *obj_list;

    color = vec(0, 0, 0);    // color값 초기화
    scene.rec.tmin = 0;
    scene.rec.tmax = INFINITY;
    obj_list = scene.objects;
    while (obj_list)
    {
        if (obj_list->type == SPHERE)
            is_hit = hit_sphere(&(scene.rec), ray, obj_list->element);
        // printf("%f %f %f\n", scene.rec.normal.x );
        if (is_hit == 1)
        {
            color = phong_light(&scene, ray);
            // printf("%f %f %f\n", color.x, color.y, color.z);
            // color = vec(0.1,1,0);
            scene.rec.tmax = scene.rec.t;
        }
        obj_list = obj_list->next;
    }
    return ((int)(255.999 * color.x) << 16 | (int)(255.999 * color.y) << 8 | (int)(255.999 * color.z));
}

void print_scene(t_scene scene, t_data image)
{
    t_ray   ray;
    t_vec   vertical;
    t_vec	horizontal;
    t_vec   lower_left_corner;
    double  u;
    double  v;
    int     i;
    int     j;

    // lower_left_corner
    vertical = vec(0, -scene.viewport.height, 0);
    horizontal = vec(scene.viewport.width, 0, 0);
    lower_left_corner = 
        vec(scene.camera.origin.x + (- horizontal.x / 2) + (-vertical.x / 2) + (0),
        scene.camera.origin.y + (- horizontal.y / 2) + (- vertical.y / 2) + (0),
        scene.camera.origin.z + (- horizontal.z / 2) + (-vertical.z / 2) + (-scene.viewport.focal_length));
    // ray
    ray.origin = scene.camera.origin;   // 카메라에서 나오는 ray
    j = scene.size.height;
    while (--j >= 0)
    {
        i = -1;
        while (++i < scene.size.width)
        {
            u = (double)i / (scene.size.width - 1);
			v = (double)j / (scene.size.height - 1);
			ray.dir = 
                vec(lower_left_corner.x + u * horizontal.x + v * vertical.x - ray.origin.x,
			    lower_left_corner.y + u * horizontal.y + v * vertical.y - ray.origin.y,
			    lower_left_corner.z + u * horizontal.z + v * vertical.z - ray.origin.z);
			my_mlx(&image, i, j, ray_color(ray, scene));
        }
    }
}
