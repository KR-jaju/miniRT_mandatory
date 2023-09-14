#include <stdlib.h>
#include "scene.h"

int	dummy_scene(t_scene *scene)
{
	scene->objects = NULL;
	scene->meshs = NULL;

	scene->camera.eye = (t_vec3){0, 5, 0};
	scene->camera.look_at = (t_vec3){5, 0, 0};
	scene->camera.up = (t_vec3){0, 1, 0};
	scene->camera.fov = 100;

	scene->light.position = (t_vec3){0, 0, 0};
	scene->light.color = (t_vec3){1, 0, 0};

	scene->ambient_light = (t_vec3){0, 0, 0.5};
	return (0);
}
