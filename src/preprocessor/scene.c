#include <stdlib.h>
#include "scene.h"

void	preprocess_object(t_object *obj);
void	preprocess_camera(t_camera *cam);

int	allocate_array(t_object *objects, int n_objects)
{
	int	i;

	i = 0;
	while (i < n_objects)
	{
		objects[i].vertices = malloc(sizeof(t_vec3) \
									* objects[i].mesh->n_vertices);
		objects[i].vertex_normals = malloc(sizeof(t_vec3) \
									* objects[i].mesh->n_vertices);
		objects[i].triangles = malloc(sizeof(t_triangle) \
									* objects[i].mesh->n_triangles);
		if (!objects[i].vertices \
			|| !objects[i].vertex_normals \
			|| !objects[i].triangles)
			return (-1);
		i++;
	}
	return (0);
}

int	preprocess_scene(t_scene *scene)
{
	int	i;

	if (allocate_array(scene->objects, scene->n_objects) == -1)
		return (-1);
	i = 0;
	while (i < scene->n_objects)
	{
		preprocess_object(&scene->objects[i]);
		i++;
	}
	preprocess_camera(&scene->camera);
	return (0);
}
