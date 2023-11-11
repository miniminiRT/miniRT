/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_operator3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 14:21:36 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/22 14:22:04 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	vec_mul_vec(t_vec v1, t_vec v2)
{
	t_vec	v;

	v.x = v1.x * v2.x;
	v.y = v1.y * v2.y;
	v.z = v1.z * v2.z;
	return (v);
}

t_vec	vec_min(t_vec v1, t_vec v2)
{
	t_vec	new;

	if (v1.x < v2.x)
		new.x = v1.x;
	else
		new.x = v2.x;
	if (v1.y < v2.y)
		new.y = v1.y;
	else
		new.y = v2.y;
	if (v1.z < v2.z)
		new.z = v1.z;
	else
		new.z = v2.z;
	return (new);
}
