/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:54:21 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/22 15:26:35 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vec	set_face_normal(t_vec normal, t_ray ray)
{
	if (vec_dot(ray.dir, normal) > 0.0)
		return (vec(-normal.x, -normal.y, -normal.z));
	return (normal);
}

int	is_invalid(char **str)
{
	int	i;

	i = 0;
	if (str[0])
	{
		if (str[0][0] == '-')
		{
			if (!(str[0][1] >= '1' && str[0][1] <= '9'))
				return (1);
			i++;
		}
		while (str[0][i])
		{
			if (!(str[0][i] >= '0' && str[0][i] <= '9'))
				return (1);
			i++;
		}
	}
	else if (str[1])
	{
		i = 0;
		while (str[1][i])
		{
			if (!(str[0][i] >= '0' && str[0][i] <= '9'))
				return (1);
			i++;
		}
	}
	return (0);
}

double	ft_strtod(char	*src)
{
	int		i;
	int		minus;
	double	natural_num;
	double	decimal_num;
	char	**str;

	str = ft_split(src, '.');
	if (is_invalid(str))
	{
		printf("invalide input error\n");
		exit(0);
	}
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
	{
		i = ft_strlen(str[1]);
		decimal_num = ft_atoi(str[1]);
		decimal_num /= pow(10, i);
	}
	if (natural_num < 0)
		natural_num *= -1;
	free_all(str);
	return (minus * (natural_num + decimal_num));
}

void	error(void)
{
	write(2, "error\n", 6);
	exit(1);
}

void	free_all(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] == 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
