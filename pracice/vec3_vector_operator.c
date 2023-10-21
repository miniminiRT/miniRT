/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_vector_operator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:15:55 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/13 14:19:00 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vec3_length_squared(t_vec3 v)
{
	return (v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

t_vec3	vec3_unit(t_vec3 v)
{
	double	len;

	len = vec3_length(v);
	return (vec3_create(v.e[0] / len, v.e[1] / len, v.e[2] / len));
}
