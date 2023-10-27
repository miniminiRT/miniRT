/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operator1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:01:52 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/22 10:19:35 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	vec(double x, double y, double z)
{
	t_vec	out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

// +
t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	out;

	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;
	out.z = v1.z + v2.z;
	return (out);
}

// -
t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	out;

	out.x = v1.x - v2.x;
	out.y = v1.y - v2.y;
	out.z = v1.z - v2.z;
	return (out);
}

//	* (t 곱해서 크기 늘리기)
t_vec	vec_mul(t_vec v1, double t)
{
	t_vec	out;

	out.x = v1.x * t;
	out.y = v1.y * t;
	out.z = v1.z * t;
	return (out);
}

// %
t_vec	vec_div(t_vec v1, double t)
{
	t_vec	out;

	out.x = v1.x / t;
	out.y = v1.y / t;
	out.z = v1.z / t;
	return (out);
}

// A^2 + B^2 + C^2


// 원점 좌표와 방향 벡터를 이용해서 벡터의 끝 점 알기
t_vec	ray_at(t_ray ray, double t)
{
	t_vec	out;

	out.x = ray.origin.x + ray.dir.x * t;
	out.y = ray.origin.y + ray.dir.y * t;
	out.z = ray.origin.z + ray.dir.z * t;
	return (out);
}