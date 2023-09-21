#include <stdlib.h>
#include "scene.h"
#include "mesh.h"
#include "debug.h"

t_object	dummy_object(t_mesh *mesh, t_vec3 color)
{
	t_object object;

	object.mesh = mesh;
	object.position = (t_vec3){0, 0, 0};
	object.rotation = (t_vec3){0, 0, 0};
	object.scale = (t_vec3){1, 1, 1};
	object.material.color = color;

	// printf("mesh->n_vertices: %d\n", mesh->n_vertices);
	// object.vertices = malloc(sizeof(t_vec3) * mesh->n_vertices);
	// object.normals = malloc(sizeof(t_vec3) * mesh->n_vertices);

	return (object);
}


enum e_meshs
{
	PLANE,
	SPHERE,
	CYLINDER
};

void set_objects(t_scene *scene)
{
	t_vec3 red = (t_vec3){1, 0, 0};
	t_vec3 green = (t_vec3){0, 1, 0};
	t_vec3 blue = (t_vec3){0, 0, 1};

	scene->objects[0] = dummy_object(&scene->meshs[PLANE], blue);

	scene->objects[1] = dummy_object(&scene->meshs[CYLINDER], green);
	scene->objects[1].position = (t_vec3){-2, 4, 0};

	scene->objects[2] = dummy_object(&scene->meshs[CYLINDER], green);
	scene->objects[2].position = (t_vec3){0, 2, 0};

	scene->objects[3] = dummy_object(&scene->meshs[CYLINDER], green);
	scene->objects[3].position = (t_vec3){2, 1, 0};

	// sphere_init(&scene->meshs[1], 20, 20);
	// cylinder_init(&scene->meshs[2], 10);
	// scene->objects[0] = dummy_object(&scene->meshs[0], (t_vec3){0, 0, 1});
	// scene->objects[1] = dummy_object(&scene->meshs[1], (t_vec3){1, 0, 0});
	// scene->objects[1].position = (t_vec3){0, 1, 0};
	// scene->objects[2] = dummy_object(&scene->meshs[2], (t_vec3){0, 1, 0});
	// scene->objects[2].position = (t_vec3){0, 1, 0};
}

void set_camera(t_scene *scene)
{
	scene->camera.position = (t_vec3){0, 2, -5};
	scene->camera.right = vec3_normalize((t_vec3){1, 0, 0});
	scene->camera.up = vec3_normalize((t_vec3){0, 1, 0});
	scene->camera.forward = vec3_normalize((t_vec3){0, -2, 5});
	scene->camera.fov = 100;
}

void set_light(t_scene *scene)
{
	scene->light.position = (t_vec3){-2, 4, 0};
	scene->light.color = (t_vec3){3, 3, 3};
	scene->ambient_light = (t_vec3){0.3, 0.3, 0.3};
}


int	dummy_scene(t_scene *scene)
{
	// 초기화 작업
	const int n_meshs = 3;
	const int n_objects = 4;
	scene->n_meshs = n_meshs;
	scene->n_objects = n_objects;
	scene->objects = malloc(sizeof(t_object) * n_objects);
	plane_init(&scene->meshs[0]);
	sphere_init(&scene->meshs[1], 10, 10);
	cylinder_init(&scene->meshs[2], 10);

	// 오브젝트, 카메라, 빛 세팅
	set_objects(scene);
	set_camera(scene);
	set_light(scene);
	return (0);
}
