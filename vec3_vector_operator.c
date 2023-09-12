/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_vector_operator.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:15:55 by jonhan            #+#    #+#             */
/*   Updated: 2023/09/12 16:04:47 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

double	vec3_length(t_vec3 v)
{
	return (sqrt(vec3_length_squared(v)));
}

double	vec3_length_squared(t_vec3 v)
{
    return (v.e[0] * v.e[0] + v.e[1] * v.e[1] + v.e[2] * v.e[2]);
}
