/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seojchoi <seojchoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 17:05:38 by seojchoi          #+#    #+#             */
/*   Updated: 2023/11/28 17:05:40 by seojchoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	set_size(t_scene *scene)
{
	scene->size.aspect_ratio = 16.0 / 9.0;
	scene->size.width = 1000;
	scene->size.height
		= (int)((double)scene->size.width / scene->size.aspect_ratio);
	return ;
}

void	init_scene(t_scene *scene)
{
	scene->objects = NULL;
	scene->lights = NULL;
	return ;
}

int	file_open(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd < 0)
		file_error();
	return (fd);
}

void	set_by_type(t_scene *scene, char **res, int *id)
{
	if (!(*res))
		empty_line();
	if (ft_strncmp(res[0], "A", 1) == 0)
		set_ambient(scene, res);
	else if (ft_strncmp(res[0], "C", 1) == 0)
		set_camera(scene, res);
	else if (ft_strncmp(res[0], "L", 1) == 0)
		set_lights(scene, res);
	else
		set_objects(scene, res, id);
}

t_scene	set_scene(char *argv)
{
	t_scene	scene;
	char	*str;
	char	**res;
	int		fd;
	int		id;

	id = 0;
	fd = file_open(argv);
	str = get_next_line(fd);
	if (!str)
		empty_line();
	init_scene(&scene);
	while (str)
	{
		str = ft_strtrim(str, "\n");
		line_check(str);
		res = ft_split(str, ' ');
		set_by_type(&scene, res, &id);
		free(str);
		free_all(res);
		str = get_next_line(fd);
	}
	set_size(&scene);
	set_viewport(&scene);
	return (scene);
}
