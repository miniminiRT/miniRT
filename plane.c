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

int	hit_cylinder(t_hit_record *rec, t_ray ray, t_cylinder *cy)
{
	double	denom;
	double	t;
	double	s;

	denom = vec_dot(cy->normal, vec_mul(ray.dir, -1));
	if (denom > 0)
	{
		t = vec_dot(cy->center, cy->normal) - vec_dot(cy->normal, ray.origin);
		t /= vec_dot(cy->normal, ray.dir);
		if (t > 0)
		{
			if (t < rec->tmin || t > rec->tmax)
			{
				return (0);
			}
			//
			// ray.origin + t * ray.dir - cy.center의 크기가 0보다 크고 r보다 작으면 그려주기
			s = vec_length(vec_sub(vec_add(ray.origin, vec_mul(ray.dir, t)), cy->center));
			if (!(s > 0.0 && s <= cy->radius))
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
