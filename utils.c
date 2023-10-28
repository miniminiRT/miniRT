/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:54:21 by seojchoi          #+#    #+#             */
/*   Updated: 2023/10/27 20:54:17 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	is_valid(char **str, char *src)
{
	if (src[0] == '.')
		return (0);
	if (str[0] && !ft_strncmp(ft_itoa((ft_atoi(str[0]))), str[0], ft_strlen(str[0])))
	{
		if (!str[1])
			return (1);
		if (str[1] && !ft_strncmp(ft_itoa((ft_atoi(str[1]))), str[1], ft_strlen(str[1])))
			return (1);
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
	minus = 1;
	natural_num = 0.0;
	decimal_num = 0.0;
	if (!is_valid(str, src))
	{
		printf("parsing error\n");	
		exit(1);    // 파싱 ㅇㅔ러처리하기
	}
	if (str[0])
		natural_num = ft_atoi(str[0]);
	if (str[1])
	{
		i = ft_strlen(str[1]);
		decimal_num = ft_atoi(str[1]);
		decimal_num /= pow(10, i);
	}
	if (natural_num < 0)
	{
		natural_num *= -1;
		minus = -1;
	}
	//free(str);
	return (minus * (natural_num + decimal_num));
}

