#include "miniRT.h"


int	hit_cylinder(t_hit_record *rec, t_ray ray, t_cylinder *cl)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	t_vec ce;

	t_vec z_max = vec_add(cl->center, vec_mul(cl->normal, cl->height/2));
	// t_vec z_min = vec_sub(cl->center, vec_mul(cl->normal, cl->height/2));
	a = vec_dot(ray.dir, cl->normal);
	a = a * a - 1;
	ce = vec_sub(ray.origin, cl->center);
	b = vec_dot(ray.dir, cl->normal) * vec_dot(ce, cl->normal) - vec_dot(ce, ray.dir);
	c = (cl->radius * cl->radius) -  vec_dot(ce, ce) + vec_dot(ce, ray.dir);

	discriminant = (b * b) - (a * c);
	if (discriminant < 0)  // 판별식이 음수이면 해가 없음.
		return (0);
	double sqrtd = sqrt(discriminant);
	double root = (- b - sqrtd) / a;
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-b + sqrtd) / (2 * a);
		if (root < rec->tmin || root > rec->tmax)
			return (0);
	}
	rec->t = root;
	rec->tmax = rec->t;
	rec->p = ray_at(ray, rec->t);
	rec->albedo = cl->color;
	rec->normal = cl->normal;
	return (1);
}
