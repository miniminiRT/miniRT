
#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlxset.h"
# include "libft/libft.h"

enum e_type{
	SPHERE,
	PLANE,
	CYLINDER,
	LIGHT,
};

typedef struct s_vec{
	double	x;
	double	y;
	double	z;
}	t_vec;

typedef struct s_viewport{
	int		width;
	int		height;
	double	focal_length;	
	// double	aspect_ratio;
}	t_viewport;

typedef struct s_size
{
    int     width;
    int     height;
    double  aspect_ratio;
}   t_size;

typedef struct s_camera{
	t_vec	origin;
	t_vec	dir;
	double	fov;
}	t_camera;

typedef struct s_object{
	int				id;
	enum e_type		type;
	void			*element;
	struct s_object	*next;
	// t_vec	albedo;
}	t_object;

typedef struct s_sphere{
	t_vec	center;
	t_vec	albedo;
	double	radius;
}	t_sphere;

typedef	struct s_plane
{
	t_vec	point;
	t_vec	normal;
	t_vec	color;
}	t_plane;

typedef	struct s_cylinder
{
	t_vec	center;
	t_vec	normal;
	double	radius;
	double	height;
	t_vec	color;
}	t_cylinder;


typedef	struct	s_ambient{
	t_vec	color;
	double	light_ratio;
}	t_ambient;

typedef struct s_light{
	t_vec	origin;
	t_vec	light_color;
	double	brightness;
	struct s_light	*next;
}	t_light;

typedef struct s_ray{
	t_vec	origin;
	t_vec	dir;
	double	t;
}	t_ray;

typedef struct s_util{
	t_vec   oc;
	double  a;
    double  b;
    double  c;
	double  sqrtd;
}	t_util;

enum	e_side{
	IN,
	OUT
};

typedef struct s_print{
	t_vec   vertical;
    t_vec	horizontal;
    t_vec   lower_left_corner;
    double  u;
    double  v;
}	t_print;

typedef struct s_hit_record{
	t_vec		p; //object와 ray의 교점;
	t_vec		normal; //법선벡터
	enum e_side	side;
	double		tmin;
	double		tmax;
	double		t;
	t_vec		albedo;
}	t_hit_record;

typedef struct s_scene{
	t_viewport	viewport;
	t_camera	camera;
	t_size		size;
	t_object	*objects;
	t_light		*lights;
	t_ray		ray;
	t_ambient	ambient;
	t_hit_record	rec;
}	t_scene;

typedef struct	s_phong{
	t_vec	diffuse;
	t_vec	light_dir;
	double	kd;
	t_vec	specular;
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	spec;
	double	ksn;
	double	ks;
	double	brightness;
	t_vec	light_sum;
	t_ray	light_ray;
	double	light_len;
}	t_phong;

t_vec	vec(double x, double y, double z);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_mul(t_vec v1, double t);
t_vec	vec_div(t_vec v1, double t);

double	vec_length(t_vec v1);
double	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_cross(t_vec v1, t_vec v2);
t_vec	vec_unit(t_vec v);

t_vec	vec_mul_vec(t_vec v1, t_vec v2);
t_ray	ray(t_vec origin, t_vec dir);
int		hit(t_scene *scene, t_ray r, t_hit_record *rec, int id);
int		hit_sphere(t_hit_record *rec, t_ray ray, t_sphere *sp);
int	in_shadow(t_scene *scene, t_ray r, double light_len, int id);
t_vec	reflect(t_vec v, t_vec n);
t_vec	point_light_get(t_scene *scene, t_light *light, int id);
t_vec	phong_light(t_scene	*scene, int id);

// vec_operator1
t_vec	vec(double x, double y, double z);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_mul(t_vec v1, double t);
t_vec	vec_div(t_vec v1, double t);
t_vec	ray_at(t_ray ray, double t);

// vec_operator2
double	length_squared(double x, double y, double z);
double	vec_length(t_vec v1);
double	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_cross(t_vec v1, t_vec v2);
t_vec	vec_unit(t_vec v);

// vec_operator3
t_vec	vec_mul_vec(t_vec v1, t_vec v2);
t_vec	vec_min(t_vec v1, t_vec v2);

t_scene set_scene(void);
void print_scene(t_scene scene, t_data image);
void	my_mlx(t_data *data, int x, int y, int color);


double	ft_strtod(char	*src);

#endif