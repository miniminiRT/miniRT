/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:08:42 by seojchoi          #+#    #+#             */
/*   Updated: 2023/12/01 15:01:04 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include "mlxset.h"
# include "../libft/libft.h"
# define EPSILON 1e-6

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
	double		width;
	double		height;
	double		focal_length;
}	t_viewport;

typedef struct s_size
{
	int		width;
	int		height;
	double	aspect_ratio;
}	t_size;

typedef struct s_camera{
	t_vec	origin;
	t_vec	dir;
	t_vec	x_axis;
	t_vec	y_axis;
	double	ratio;
	t_vec	left_top;
	t_vec	change_x;
	t_vec	change_y;
	double	fov;
}	t_camera;

typedef struct s_object{
	int				id;
	enum e_type		type;
	void			*element;
	struct s_object	*next;
}	t_object;

typedef struct s_sphere{
	t_vec	center;
	t_vec	albedo;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec	point;
	t_vec	normal;
	t_vec	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec	center;
	double	radius;
	double	height;
	t_vec	normal;
	t_vec	color;
	t_vec	top_center;
	t_vec	base_center;
	t_vec	h;
}	t_cylinder;

typedef struct s_ambient{
	t_vec	color;
	double	light_ratio;
}	t_ambient;

typedef struct s_light{
	t_vec			origin;
	t_vec			light_color;
	double			brightness;
	struct s_light	*next;
}	t_light;

typedef struct s_ray{
	t_vec	origin;
	t_vec	dir;
	double	t;
}	t_ray;

typedef struct s_util{
	double	a;
	double	b;
	double	c;
	double	sqrtd;
	double	root;
	double	root1;
	double	discriminant;
}	t_util;

enum	e_side{
	IN,
	OUT
};

typedef struct s_print{
	t_vec	vertical;
	t_vec	horizontal;
	t_vec	lower_left_corner;
	double	u;
	double	v;
}	t_print;

typedef struct s_hit_record{
	t_vec		p;
	t_vec		normal;
	enum e_side	side;
	double		tmin;
	double		tmax;
	double		t;
	t_vec		albedo;
}	t_hit_record;

typedef struct s_scene{
	t_viewport		viewport;
	t_camera		camera;
	t_size			size;
	t_object		*objects;
	t_light			*lights;
	t_ray			ray;
	t_ambient		ambient;
	t_hit_record	rec;
}	t_scene;

typedef struct s_phong{
	t_vec	diffuse;
	t_vec	light_dir;
	double	kd;
	t_vec	specular;
	t_vec	view_dir;
	t_vec	reflect_dir;
	double	spec;
	double	brightness;
	t_vec	light_sum;
	t_ray	light_ray;
	double	light_len;
}	t_phong;

typedef struct s_setobj
{
	char		**center;
	char		**albedo;
	t_object	*object;
	t_object	*iter;
}	t_setobj;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_data		image;
	t_scene		update;
}	t_vars;

typedef struct s_set_viewport
{
	t_vec	lookfrom;
	t_vec	lookat;
	t_vec	vup;
	t_vec	w;
	t_vec	u;
	t_vec	v;
}	t_set_viewport;

//setting object
void	set_plane(t_scene *scene, char **res, int *id);
void	set_cylinder(t_scene *scene, char **res, int *id);
void	set_sphere(t_scene *scene, char **res, int *id);
void	set_objects(t_scene *scene, char **res, int *id);
void	set_lights(t_scene *scene, char **res);
void	set_ambient(t_scene *scene, char **res);
void	set_camera(t_scene *scene, char **res);
void	set_viewport(t_scene *scene);

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
int		hit(t_scene *scene, t_ray r, t_hit_record rec, int id);
int		hit_sphere(t_hit_record *rec, t_ray ray, t_sphere *sp);
int		in_shadow(t_scene *scene, t_ray r, double light_len, int id);
t_vec	reflect(t_vec v, t_vec n);
t_vec	point_light_get(t_scene *scene, t_light *light, int id, int *is_shadow);
t_vec	phong_light(t_scene	*scene, int id, int is_shadow);

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

// print_scene_utils
int		rgb_to_color(t_vec color);
t_vec	get_lower_left_corner(t_scene *scene, \
			t_vec horizontal, t_vec vertical, t_vec w);
t_vec	get_ray_dir(t_print p, t_ray ray);
void	set_viewport_vector(t_set_viewport *sv, t_scene *scene);
void	set_print_vector(t_scene *scene, t_print *print_vec, t_set_viewport sv);

// error
void	wrong_type_double(void);
void	ratio_error(int type);
void	degree_error(void);
void	wrong_type_input(void);
void	three_input_error(void);
void	malloc_error(void);
void	file_error(void);
void	empty_line(void);

// check_range
int		range_check_light(double num);
int		range_check_vector(double num);
int		range_check_degree(double num);
int		range_check_color(double num);

t_scene	set_scene(char *argv);
void	print_scene(t_scene *scene, t_data image);
void	my_mlx(t_data *data, int x, int y, int color);

void	input_arg_count_error(void);
int		tp_arr_size(char **arr);
void	free_all(char **arr);
double	ft_strtod(char *src);
int		count_dot(char *str);
int		arr_size(char **str);
void	file_name_check(char *f_name);
void	line_check(char *str);
int		hit_plane(t_hit_record *rec, t_ray ray, t_plane *pl);
int		hit_cylinder(t_hit_record *rec, t_ray ray, t_cylinder *cy);
t_vec	set_face_normal(t_vec normal, t_ray ray);
int		get_root(t_util *util, t_hit_record *rec);
void	change_location(t_vars *vars, int keycode);
void	change_angle(t_vars *vars, int keycode);
void	get_src_for_disciminant(t_util	*util, t_ray ray, t_cylinder *cy);
void	set_light_list(t_scene *scene, t_light *lights);
void	light_vec_check(char **res, char **origin, char **color);
#endif
