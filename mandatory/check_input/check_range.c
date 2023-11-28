/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_range.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:04:33 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/28 17:04:37 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

int	range_check_light(double num)
{
	if (!(num >= 0.0 && num <= 1.0))
		return (1);
	return (0);
}

int	range_check_vector(double num)
{
	if (!(num >= -1.0 && num <= 1.0))
		return (1);
	return (0);
}

int	range_check_degree(double num)
{
	if (!(num >= 0.0 && num <= 180.0))
		return (1);
	return (0);
}

int	range_check_color(double num)
{
	if (!(num >= 0.0 && num <= 1.0))
		return (1);
	return (0);
}
