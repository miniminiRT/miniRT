/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 15:33:58 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/28 17:06:31 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	wrong_type_double(void)
{
	printf("Error\n");
	printf("input value must be double type [00.00]\n");
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

void	wrong_type_input(void)
{
	printf("Error\n");
	printf("enter input in the following format ./miniRT [file_name].rt\n");
	exit(1);
}
