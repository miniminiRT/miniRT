#include "miniRT.h"

void	set_size(t_scene *scene)
{
	scene->size.aspect_ratio = 16.0 / 9.0;
	scene->size.width = 1000;
	scene->size.height
		= (int)((double)scene->size.width / scene->size.aspect_ratio);
	return ;
}

void	set_viewport(t_scene *scene)
{
	double	theta;
	double	h;

	theta = (scene->camera.fov * M_PI) / 180.0;
	h = tan(theta / 2);
	scene->viewport.focal_length = 1.0;
	scene->viewport.height = 2.0 * h * scene->viewport.focal_length;
	scene->viewport.width = scene->size.aspect_ratio * scene->viewport.height;
	return ;
}

void	init_scene(t_scene *scene)
{
	scene->objects = NULL;
	scene->lights = NULL;
	return ;
}

t_scene	set_scene(char *argv)
{
	t_scene	scene;
	char	*str;
	char	**res;
	int		fd;
	int		id;

	id = 0;
	fd = open(argv, O_RDONLY);
	if (fd < -1)
		error();
	str = get_next_line(fd);
	if (!str)
		error();
	init_scene(&scene);
	while (str)
	{
		str = ft_strtrim(str, "\n");
		res = ft_split(str, ' ');
		if (ft_strncmp(res[0], "A", 1) == 0)
			set_ambient(&scene, res);
		else if (ft_strncmp(res[0], "C", 1) == 0)
			set_camera(&scene, res);
		else if (ft_strncmp(res[0], "L", 1) == 0)
			set_lights(&scene, res);
		else
			set_objects(&scene, res, &id);
		free(str);
		free_all(res);
		str = get_next_line(fd);
	}
	set_size(&scene);
	set_viewport(&scene);
	return (scene);
}