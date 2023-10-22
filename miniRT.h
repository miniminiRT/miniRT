/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:26:18 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/22 10:22:21 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>

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
	double	aspect_ratio;
}	t_viewport;


typedef struct s_camera{
	t_vec	origin;
	t_vec	dir;
}	t_camera;

typedef struct s_object{
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

typedef struct s_light{
	t_vec	origin;
	t_vec	light_color;
	double	brightness;
}	t_light;

typedef struct s_ray{
	t_vec	origin;
	t_vec	dir;
	double	t;
}	t_ray;

enum	e_side{
	IN,
	OUT
};

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
	t_object	*objects;
	t_object	*lights;
	t_ray		ray;
	t_vec		ambient;
	// t_hit_record	rec;
}	t_scene;

t_vec	vec(double x, double y, double z);
t_vec	vec_add(t_vec v1, t_vec v2);
t_vec	vec_sub(t_vec v1, t_vec v2);
t_vec	vec_mul(t_vec v1, double t);
t_vec	vec_div(t_vec v1, double t);

double	vec_length(t_vec v1);
double	vec_dot(t_vec v1, t_vec v2);
t_vec	vec_cross(t_vec v1, t_vec v2);
t_vec	vec_unit(t_vec v);












#endif