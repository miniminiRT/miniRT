#include "miniRT.h"

int	hit_plane(t_hit_record *rec, t_ray ray, t_plane *pl)
{ 
	double	denom;
	double	t;

	denom = vec_dot(pl->normal, vec_mul(ray.dir, -1));
	if (denom > 0)
	{
		t = vec_dot(pl->point, pl->normal) - vec_dot(pl->normal, ray.origin);
		t /= vec_dot(pl->normal, ray.dir);
		if (t > 0)
		{
			if (t < rec->tmin || t > rec->tmax)
			{
				return (0);
			}
			rec->tmax = t;
			rec->t = t;
			rec->p = ray_at(ray, rec->t);
			rec->albedo = pl->color;
			rec->normal = pl->normal;
			return (1);
		}
	}
	return (0);  // false
}

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
			{
				return (0);
			}
			//
			// ray.origin + t * ray.dir - cy.center의 크기가 0보다 크고 r보다 작으면 그려주기
			s = vec_length(vec_sub(vec_add(ray.origin, vec_mul(ray.dir, t)), center));
			if (!(s > 0.0 && s <= cy->radius))
				return (0);
			//
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
			{
				return (0);
			}
			//
			// ray.origin + t * ray.dir - cy.center의 크기가 0보다 크고 r보다 작으면 그려주기
			s = vec_length(vec_sub(vec_add(ray.origin, vec_mul(ray.dir, t)), center));
			if (!(s >= 0.0 && s <= cy->radius))
				return (0);
			//
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

int	hit_cylinder(t_hit_record *rec, t_ray ray, t_cylinder *cy)
{
	double	a;
	double	b;
	double	c;
	t_vec	h;
	t_vec	w;
	double	discriminant;
	double	sqrtd;
	double	root;
	double	size;

	// 원기둥 top center, base center 구하기
	t_vec	max;
	t_vec	min;
	t_ray	up;
	up.dir = cy->normal;
	up.origin = cy->center;
	up.t = cy->height / 2;
	max = ray_at(up, cy->height / 2);
	t_ray	down;
	down.dir = vec_mul(cy->normal, -1);
	down.origin = cy->center;
	down.t = cy->height / 2;
	min = ray_at(down, cy->height / 2);

	//  판별식에 사용할 a, b, c 구하기
	h = vec_div(vec_sub(max, min), vec_length(vec_sub(max, min)));
	// h = vec_unit(cy->normal);
	a = vec_dot(ray.dir, ray.dir) - vec_dot(ray.dir, h) * vec_dot(ray.dir, h);

	w = vec_sub(ray.origin, min);
	b = vec_dot(ray.dir, w) - vec_dot(ray.dir, h) * vec_dot(w, h);
	b *= 2;

	c = vec_dot(w, w) - vec_dot(w, h) * vec_dot(w, h) - cy->radius * cy->radius;

	// 판별식
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	sqrtd = sqrt(discriminant);
    root = (-b - sqrtd) / (2 * a);
	if (root < rec->tmin || root > rec->tmax)
	{
		root = (-b + sqrtd) / (2 * a);
		if (root < rec->tmin || root > rec->tmax)
			return (0);
	}

	// 해가 있다면 기둥인지, 바닥인지 확인하고 높이 만큼만 그려주기
	size = vec_dot(vec_sub(ray_at(ray, root), min), h);
	if (size < 0.0)
		return (is_base(rec, ray, cy, min));
	if (size > vec_length(vec_sub(max, min)))
		return (is_top(rec, ray, cy, max));
	if (size >= 0 && size <= vec_length(vec_sub(max, min)))
	{
		rec->tmax = root;
		rec->t = root;
		rec->p = ray_at(ray, rec->t);
		rec->albedo = cy->color;

		// t_vec  normal;
		t_vec c;
	
		t_ray	n;

		n.dir = cy->normal;
		n.origin = min;
		n.t = size;
		c = ray_at(n, size);

		// normal = vec_div((vec_sub(rec->p, c)), vec_length(vec_sub(rec->p, c)));
		// normal = vec_unit(vec_sub(rec->p, c));
		t_vec cp = vec_sub(rec->p, cy->center);
		t_vec qp = vec_sub(cp, vec_mul(cy->normal, vec_dot(cp, cy->normal)));
		rec->normal = vec_unit(qp);
		// rec->normal = set_face_normal(rec->normal, ray);  // 안, 밖 고려해서 법선벡터 바꾸기
		return (1);
	}
	return (0);
}
