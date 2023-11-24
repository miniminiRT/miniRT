/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operator1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 15:01:52 by jonhan            #+#    #+#             */
/*   Updated: 2023/11/20 15:15:42 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

t_vec	vec(double x, double y, double z)
{
	t_vec	out;

	out.x = x;
	out.y = y;
	out.z = z;
	return (out);
}

t_vec	vec_add(t_vec v1, t_vec v2)
{
	t_vec	out;

	out.x = v1.x + v2.x;
	out.y = v1.y + v2.y;
	out.z = v1.z + v2.z;
	return (out);
}

t_vec	vec_sub(t_vec v1, t_vec v2)
{
	t_vec	out;

	out.x = v1.x - v2.x;
	out.y = v1.y - v2.y;
	out.z = v1.z - v2.z;
	return (out);
}

t_vec	vec_mul(t_vec v1, double t)
{
	t_vec	out;

	out.x = v1.x * t;
	out.y = v1.y * t;
	out.z = v1.z * t;
	return (out);
}

t_vec	vec_div(t_vec v1, double t)
{
	t_vec	out;

	out.x = v1.x / t;
	out.y = v1.y / t;
	out.z = v1.z / t;
	return (out);
}
