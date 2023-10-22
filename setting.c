#include "miniRT.h"

void set_size(t_scene *scene)
{
    scene->size.aspect_ratio = 16.0 / 9.0;
    scene->size.width = 1000;  // mlx랑 통일
    scene->size.height = (int)((double)scene->size.width / scene->size.aspect_ratio);
}

void set_viewport(t_scene *scene)
{
    scene->viewport.height = 2.0;
    scene->viewport.width = scene->size.aspect_ratio * scene->viewport.height;
    scene->viewport.focal_length = 1.0;
}

void set_camera(t_scene *scene)
{
    scene->camera.origin = ;
    scene->camera.dir = ;
}

void set_ambient(t_scene *scene)
{
    scene->ambient.x = ;
    scene->ambient.y = ;
    scene->ambient.z = ;
}

void set_lights(t_scene *scene)
{
    
}

void set_objects(t_scene *scene)
{

}

t_scene set_scene(void)
{
    t_scene scene;

    set_size(&scene);
    set_viewport(&scene);
    set_camera(&scene);
    set_ambient(&scene);
    set_lights(&scene);
    set_objects(&scene);
    return (scene);
}