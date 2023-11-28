/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:33:58 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/28 16:51:02 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

void	wrong_type_double(void)
{
	printf("Error\nwrong_type error\n");  // 나중에 오류 문구 수정
	exit(1);
}

void	ratio_error(int type)
{
	if (type == 1)
		printf("Error\nyou must set ratio in range [0.0,1.0]\n");
	else if (type == 2)
		printf("Error\nyou must set color in range [0.0-255.0]\n");
	else if (type == 3)
		printf("Error\nyou must set vector in range [-1.0,1.0]\n");
	exit(1);
}

void	degree_error(void)
{
	printf("Error\nyou must set degree in range [0,180]\n");
	exit(1);
}
