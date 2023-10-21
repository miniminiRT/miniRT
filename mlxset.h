/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxset.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:55:23 by jonhan            #+#    #+#             */
/*   Updated: 2023/10/21 14:56:52 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXSET_H
# define MLXSET_H

# include <mlx.h>

typedef struct s_vars
{
	void		*mlx;
	void		*win;
}	t_vars;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;


#endif