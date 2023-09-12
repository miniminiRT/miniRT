/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:32:19 by jonhan            #+#    #+#             */
/*   Updated: 2023/09/12 16:05:26 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H;
# define MINIRT_H;

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct e_vec3
{
	double	e[3];
}	t_vec3;

double	vec3_length_squared(t_vec3 v);
double	vec3_length(t_vec3 v);
t_vec3	vec3_init(void);
t_vec3	vec3_create(double e0, double e1, double e2);
t_vec3	vec3_negate(t_vec3 vec);
t_vec3	vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3	vec3_multiply(t_vec3 v1, double t);
t_vec3	vec3_divide(t_vec3 v, double t);


#endif