/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:32:19 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/18 19:59:25 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

typedef struct s_vec3
{
	double	e[3];
}	t_vec3;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
}	t_vars;

typedef struct s_point3
{
	double	x;
	double	y;
	double	z;
	int		color;
}	t_point3;

typedef struct s_ray
{
	t_vec3		dir;
	t_vec3	origin;
}	t_ray;


//오브젝트 구조체를 하나 만들게 되면, 각 오브젝트마다 벡터 충돌식이 다르므로 그 함수를 함수포인터로 작성
typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_vec3	albedo;
	struct s_sphere *next;

 	// int	(*hit)(struct s_world *this, t_ray *ray, double min, double max, t_hit_record *out);
}	t_sphere;

typedef struct s_hit_record
{
	t_vec3	point;
	t_vec3	normal; //법선벡터
	double	t;
	int		front_face;
	t_vec3	albedo;
}	t_hit_record;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_light
{
	t_vec3	origin;
	t_vec3	light_color;
	double	bright_ratio;
}	t_light;


// typedef struct s_object
// {
// 	t_sphere object;
	
// }

typedef struct s_map
{
	t_point3	**map;
	int			width;
	int			height;
	// int		img_width;
	// int		img_height;
}	t_map;

double	vec3_length_squared(t_vec3 v);
double	vec3_length(t_vec3 v);
t_vec3	vec3_init(void);
t_vec3	vec3_create(double e0, double e1, double e2);
t_vec3	vec3_negate(t_vec3 vec);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_multiply(t_vec3 v1, double t);
t_vec3	vec3_divide(t_vec3 v, double t);
t_vec3	vec3_unit(t_vec3 v);
t_vec3  vec3_multiply_vec3(t_vec3 v1, t_vec3 v2);
t_vec3	vmin(t_vec3 a, t_vec3 b);
t_vec3	vec3_minus(t_vec3 v1, t_vec3 v2);

t_vec3 multiply_scalar_vec3(double t, t_vec3 v);
t_vec3 multiply_vec3_scalar(t_vec3 v, double t);
double dot_product(t_vec3* u, t_vec3* v);
t_vec3 cross_product(t_vec3* u, t_vec3* v);
t_vec3 normalize_vec3(t_vec3* v);
#endif