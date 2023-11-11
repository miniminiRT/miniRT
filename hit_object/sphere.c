#include "miniRT.h"

void    set_rec(t_hit_record *rec, t_sphere *sp, t_ray ray, double root)
{
    t_vec   normal;

    rec->albedo = sp->albedo;
	rec->t = root;
    rec->tmax = rec->t;
	rec->p = ray_at(ray, rec->t);
	normal = vec_div((vec_sub(rec->p, sp->center)), sp->radius);
    // normal = vec_unit(vec_sub(rec->p, sp->center));
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
	if (discriminant < 0)
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
	return (1);
}
