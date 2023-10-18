/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basic_operator.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 14:01:55 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/18 19:58:41 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec3	vec3_init(void)
{
	t_vec3	v;

	v.e[0] = 0.0;
	v.e[1] = 0.0;
	v.e[2] = 0.0;
	return v;
}

t_vec3	vec3_create(double e0, double e1, double e2)
{
	t_vec3	v;

	v.e[0] = e0;
	v.e[1] = e1;
	v.e[2] = e2;
	return (v);
}

t_vec3	vec3_negate(t_vec3 vec)
{
	t_vec3	v;

	v.e[0] = -vec.e[0];
	v.e[1] = -vec.e[1];
	v.e[2] = -vec.e[2];
	return (v);
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.e[0] = v1.e[0] + v2.e[0];
	v.e[1] = v1.e[1] + v2.e[1];
	v.e[2] = v1.e[2] + v2.e[2];
	return (v);
}

t_vec3	vec3_minus(t_vec3 v1, t_vec3 v2)
{
	t_vec3	v;

	v.e[0] = v1.e[0] - v2.e[0];
	v.e[1] = v1.e[1] - v2.e[1];
	v.e[2] = v1.e[2] - v2.e[2];
	return (v);
}

t_vec3	vec3_multiply(t_vec3 v1, double t)
{
	t_vec3	v;

	v.e[0] = v1.e[0] * t;
	v.e[1] = v1.e[1] * t;
	v.e[2] = v1.e[2] * t;
	return (v);
}

t_vec3	vec3_divide(t_vec3 v, double t)
{
	double	inv_t;

	inv_t = 1.0 / t;
	return (vec3_multiply(v, inv_t));
}
