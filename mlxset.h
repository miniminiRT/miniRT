/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlxset.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jonhan <jonhan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 14:55:23 by jonhan            #+#    #+#             */
/*   Updated: 2023/11/23 21:37:59 by jonhan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLXSET_H
# define MLXSET_H

# include <mlx.h>
# include "miniRT.h"

# define MOVE_LEFT 0
# define MOVE_RIGHT 2
# define MOVE_UP 13
# define MOVE_DOWN 1
# define MOVE_FRONT 12
# define MOVE_BACK 14

# define ROTATE_UP 126
# define ROTATE_DOWN 125
# define ROTATE_LEFT 123
# define ROTATE_RIGHT 124

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

#endif