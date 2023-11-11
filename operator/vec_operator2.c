/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operator2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:18:30 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/22 10:31:01 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	length_squared(double x, double y, double z)
{
	return (x * x + y * y + z * z);
}

// 벡터의 크기
double	vec_length(t_vec v1)
{
	double	value;

	value = sqrt(length_squared(v1.x, v1.y, v1.z));
	return (value);
}

// 벡터의 내적
double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// 벡터의 외적
t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	out;

	out.x = v1.y * v2.z + v1.z * v2.y;
	out.y = v1.z * v2.x + v1.x * v2.z;
	out.z = v1.x * v2.y + v1.y * v2.x;
	return (out);
}

// 단위벡터
t_vec	vec_unit(t_vec v)
{
	double	len;
	t_vec	unit_v;

	len = vec_length(v);
	unit_v = vec(v.x / len, v.y / len, v.z / len);
	return (unit_v);
}
