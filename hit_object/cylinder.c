#include "../miniRT.h"

int	is_base(t_hit_record *rec, t_ray ray, t_cylinder *cy, t_vec center)
{
	double	denom;
	double	t;
	double	s;
	t_vec	n = vec_mul(cy->normal, -1);

	denom = vec_dot(n, vec_mul(ray.dir, -1));
	if (denom > 0)
	{
		t = vec_dot(center, n) - vec_dot(n, ray.origin);
		t /= vec_dot(n, ray.dir);
		if (t > 0)
		{
			if (t < rec->tmin || t > rec->tmax)
				return (0);
			s = vec_length(vec_sub(vec_add(ray.origin, vec_mul(ray.dir, t)), center));
			if (!(s > 0.0 && s <= cy->radius))
				return (0);
			rec->tmax = t;
			rec->t = t;
			rec->p = ray_at(ray, rec->t);
			rec->albedo = cy->color;
			rec->normal = n;
			return (1);
		}
	}
	return (0);
}

int	is_top(t_hit_record *rec, t_ray ray, t_cylinder *cy, t_vec center)
{
	double	denom;
	double	t;
	double	s;

	denom = vec_dot(cy->normal, vec_mul(ray.dir, -1));
	if (denom > 0)
	{
		t = vec_dot(center, cy->normal) - vec_dot(cy->normal, ray.origin);
		t /= vec_dot(cy->normal, ray.dir);
		if (t > 0)
		{
			if (t < rec->tmin || t > rec->tmax)
				return (0);
			s = vec_length(vec_sub(vec_add(ray.origin, vec_mul(ray.dir, t)), center));
			if (!(s >= 0.0 && s <= cy->radius))
				return (0);
			rec->tmax = t;
			rec->t = t;
			rec->p = ray_at(ray, rec->t);
			rec->albedo = cy->color;
			rec->normal = cy->normal;
			return (1);
		}
	}
	return (0);
}

void    set_cylinder_rec(t_hit_record *rec, t_util util, t_ray ray, t_cylinder *cy, t_vec h)
{
	t_vec	cp;
	t_vec	qp;

    rec->tmax = util.root;
	rec->t = util.root;
	rec->p = ray_at(ray, rec->t);
	rec->albedo = cy->color;
	cp = vec_sub(rec->p, cy->base_center);
	qp = vec_sub(cp, vec_mul(h, vec_dot(cp, h)));
	rec->normal = vec_unit(qp);
	rec->normal = set_face_normal(rec->normal, ray);  // 안, 밖 고려해서 법선벡터 바꾸기
}

void get_top_base_center(t_cylinder *cy)
{
	t_ray	up;
	t_ray	down;

	up.dir = vec_unit(cy->normal);
	up.origin = cy->center;
	up.t = cy->height / 2;
	cy->top_center = ray_at(up, up.t);
	down.dir = vec_unit(vec_mul(cy->normal, -1));
	down.origin = cy->center;
	down.t = cy->height / 2;
	cy->base_center = ray_at(down, down.t);
}

int	hit_cylinder(t_hit_record *rec, t_ray ray, t_cylinder *cy)
{
	t_util  util;
	t_vec	h;
	t_vec	w;
	double	size;

	get_top_base_center(cy);
	h = vec_div(vec_sub(cy->top_center, cy->base_center), cy->height);
	w = vec_sub(ray.origin, cy->base_center);
	util.a = vec_dot(ray.dir, ray.dir) - vec_dot(ray.dir, h) * vec_dot(ray.dir, h);
	util.b = vec_dot(ray.dir, w) - vec_dot(ray.dir, h) * vec_dot(w, h);
	util.b *= 2;
	util.c = vec_dot(w, w) - vec_dot(w, h) * vec_dot(w, h) - (cy->radius * cy->radius);
	if (get_root(&util, rec) == 0)  // 이거 enum으로 해 없다고 표시하면 좋을 듯
		return (0);
	size = vec_dot(vec_sub(ray_at(ray, util.root), cy->base_center), h);
	if (size < 0.0)
		return (is_base(rec, ray, cy, cy->base_center));
	if (size > cy->height)
		return (is_top(rec, ray, cy, cy->top_center));
	if (size >= 0 && size <= cy->height)
	{
		set_cylinder_rec(rec, util, ray, cy, h);   // 이거 인자 5개임
		return (1);
	}
	return (0);
}
