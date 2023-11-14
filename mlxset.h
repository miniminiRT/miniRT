/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxset.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:55:23 by jonhan            #+#    #+#             */
/*   Updated: 2023/11/14 20:50:02 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXSET_H
# define MLXSET_H

# include <mlx.h>

# define MOVE_LEFT 0
# define MOVE_RIGHT 2
# define MOVE_UP 13
# define MOVE_DOWN 1
# define MOVE_FRONT 12
# define MOVE_BACK 14

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_update
{
	t_vec	origin;
	t_vec	dir;
	double	fov;
}	t_update;

typedef struct s_vars
{
	void		*mlx;
	void		*win;
	t_data		image;
}	t_vars;

#endif