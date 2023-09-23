#include <stdlib.h>
#include "scene.h"
#include "mesh.h"
#include "debug.h"

int		preprocess_scene(t_scene *scene);

t_object	dummy_object(t_mesh *mesh, t_vec3 color)
{
	t_object	object;

	object.mesh = mesh;
	object.position = (t_vec3){0, 0, 0};
	object.rotation = (t_vec3){0, 0, 0};
	object.scale = (t_vec3){1, 1, 1};
	object.material.color = color;
	return (object);
}

void	set_objects(t_scene *scene)
{
	const t_vec3	red = (t_vec3){1, 0, 0};
	const t_vec3	green = (t_vec3){0, 1, 0};
	const t_vec3	blue = (t_vec3){0, 0, 1};
	const int		n_objects = 3;

	scene->n_objects = n_objects;
	scene->objects = malloc(sizeof(t_object) * n_objects);
	scene->objects[0] = dummy_object(&scene->meshes[MESH_SPHERE], blue);
	scene->objects[0].position = (t_vec3){-2, 0, 5};
	scene->objects[1] = dummy_object(&scene->meshes[MESH_CYLINDER], green);
	scene->objects[1].position = (t_vec3){2, 0, 5};
	scene->objects[1].scale = (t_vec3){1, 2, 1};
	scene->objects[2] = dummy_object(&scene->meshes[MESH_PLANE], red);
	scene->objects[2].position = (t_vec3){0, -1, 0};
	scene->objects[2].scale = (t_vec3){3, 3, 3};
}

void	set_camera(t_scene *scene)
{
	scene->camera.position = (t_vec3){0, 0, 0};
	scene->camera.right = vec3_normalize((t_vec3){1, 0, 0});
	scene->camera.up = vec3_normalize((t_vec3){0, 1, 0});
	scene->camera.forward = vec3_normalize((t_vec3){0, 0, 1});
	scene->camera.fov = 100;
}

void	set_light(t_scene *scene)
{
	scene->light.position = (t_vec3){-2, 4, 0};
	scene->light.color = (t_vec3){1.5, 1.5, 1.5};
	scene->ambient_light = (t_vec3){0.3, 0.3, 0.3};
}

int	dummy_scene(t_scene *scene)
{
	plane_init(&scene->meshes[MESH_PLANE]);
	sphere_init(&scene->meshes[MESH_SPHERE], 10, 10);
	cylinder_init(&scene->meshes[MESH_CYLINDER], 10);
	set_objects(scene);
	set_camera(scene);
	set_light(scene);
	preprocess_scene(scene);
	return (0);
}
