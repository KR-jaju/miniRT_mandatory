#include <stdlib.h>
#include "scene.h"

int		preprocess_object(t_object *obj);
int		preprocess_camera(t_camera *cam);

int	preprocess_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->n_objects)
	{
		if (preprocess_object(&scene->objects[i]) == -1)
			return (-1);
		i++;
	}
	preprocess_camera(&scene->camera);
	return (0);
}
