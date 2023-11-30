/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:04:50 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/28 17:04:52 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	file_name_check(char *f_name)
{
	if (f_name[ft_strlen(f_name) - 1] != 't'
		|| f_name[ft_strlen(f_name) - 2] != 'r'
		|| f_name[ft_strlen(f_name) - 3] != '.')
	{
		wrong_type_input();
		exit(1);
	}
}

int	arr_size(char **str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		i++;
	}
	return (i);
}

int	count_dot(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	line_check(char *str)
{
	if (!(*str))
		empty_line();
	else
		return ;
}
