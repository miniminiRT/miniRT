/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:54:21 by seojchoi          #+#    #+#             */
/*   Updated: 2023/12/01 15:35:39 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	set_face_normal(t_vec normal, t_ray ray)
{
	if (vec_dot(ray.dir, normal) > 0.0)
		return (vec(-normal.x, -normal.y, -normal.z));
	return (normal);
}

int	tp_arr_size(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != 0)
	{
		i++;
	}
	return (i);
}

int	is_invalid(char **str, int idx)
{
	int	i;

	if (tp_arr_size(str) > 2)
		return (1);
	i = 0;
	if (idx == 0)
	{
		if (str[idx][0] == '-')
		{
			if (!str[idx][1])
				return (1);
			i++;
		}
	}
	if (str[idx])
	{
		while (str[idx][i])
		{
			if (!(str[idx][i] >= '0' && str[idx][i] <= '9'))
				return (1);
			i++;
		}
	}
	return (0);
}

double	ft_strtod(char	*src)
{
	int		minus;
	double	natural_num;
	double	decimal_num;
	char	**str;

	str = ft_split(src, '.');
	if (is_invalid(str, 0) || is_invalid(str, 1))
		wrong_type_double();
	minus = 1;
	natural_num = 0.0;
	decimal_num = 0.0;
	if (str[0])
	{
		natural_num = ft_atoi(str[0]);
		if (str[0][0] == '-')
			minus = -1;
	}
	if (str[1])
		decimal_num = ft_atoi(str[1]) / pow(10, ft_strlen(str[1]));
	if (natural_num < 0)
		natural_num *= -1;
	free_all(str);
	return (minus * (natural_num + decimal_num));
}

void	free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
