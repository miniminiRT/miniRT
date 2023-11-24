/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operator2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 10:18:30 by jonhan            #+#    #+#             */
/*   Updated: 2023/11/20 15:15:05 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

double	length_squared(double x, double y, double z)
{
	return (x * x + y * y + z * z);
}

double	vec_length(t_vec v1)
{
	double	value;

	value = sqrt(length_squared(v1.x, v1.y, v1.z));
	return (value);
}

double	vec_dot(t_vec v1, t_vec v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	out;

	out.x = v1.y * v2.z + v1.z * v2.y;
	out.y = v1.z * v2.x + v1.x * v2.z;
	out.z = v1.x * v2.y + v1.y * v2.x;
	return (out);
}

t_vec	vec_unit(t_vec v)
{
	double	len;
	t_vec	unit_v;

	len = vec_length(v);
	unit_v = vec(v.x / len, v.y / len, v.z / len);
	return (unit_v);
}
