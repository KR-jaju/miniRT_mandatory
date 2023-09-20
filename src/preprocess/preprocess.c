#include <stdlib.h>
#include "scene.h"

void		object_fill_triangles(t_object *object);
void		object_fill_normals(t_object *object);
void		object_fill_vertices(t_object *object);
t_material	default_material(t_vec3 color);

// TODO: 메모리 할당 실패 예외처리
int	allocate_array(t_object *objects, int n_objects)
{
	t_object	*object;
	int			i;

	i = 0;
	while (i < n_objects)
	{
		object = &objects[i];
		object->vertices = malloc(sizeof(t_vec3) * object->mesh->n_vertices);
		object->vertex_normals = malloc(sizeof(t_vec3) \
									* object->mesh->n_vertices);
		object->triangles = malloc(sizeof(t_triangle) \
									* object->mesh->n_triangles);
		i++;
	}
	return (0);
}

int	preprocess_scene(t_scene *scene)
{
	int	i;

	allocate_array(scene->objects, scene->n_objects);
	i = 0;
	while (i < scene->n_objects)
	{
		object_fill_vertices(&scene->objects[i]);
		object_fill_normals(&scene->objects[i]);
		object_fill_triangles(&scene->objects[i]);
		scene->objects[i].material = \
				default_material(scene->objects[i].material.color);
		i++;
	}
	// camera_fill_image_plane_edges(scene->camera);
	// TODO: 카메라 행렬 여기서 구하기
	return (0);
}
