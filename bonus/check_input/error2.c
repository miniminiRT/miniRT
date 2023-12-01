/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:56:52 by seojchoi          #+#    #+#             */
/*   Updated: 2023/12/01 14:58:08 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	three_input_error(void)
{
	printf("Error\n");
	printf("you must set input like [a,b,c]\n");
	exit(1);
}

void	malloc_error(void)
{
	printf("Error\n");
	printf("malloc failed\n");
	exit(1);
}

void	file_error(void)
{
	printf("Error\n");
	printf("failed to open file\n");
	exit(1);
}

void	empty_line(void)
{
	printf("Error\n");
	printf("empty input is not accepted\n");
	exit(1);
}

void	input_arg_count_error(void)
{
	printf("Error\n");
	printf("input_arg_count_error\n");
	exit(1);
}
