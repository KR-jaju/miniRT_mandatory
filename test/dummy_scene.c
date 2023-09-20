#include <stdlib.h>
#include "scene.h"
#include "mesh.h"
#include "debug.h"

t_mesh	mesh_plane(void)
{
	t_mesh	plane;

	plane.vertices = malloc(sizeof(t_vec3) * 4);
	plane.vertex_normals = malloc(sizeof(t_vec3) * 4);
	plane.indices = malloc(sizeof(int) * 6);

	plane.vertices[0] = (t_vec3){-5, 0, 5};
	plane.vertices[1] = (t_vec3){-5, 0, -5};
	plane.vertices[2] = (t_vec3){5, 0, -5};
	plane.vertices[3] = (t_vec3){5, 0, 5};

	plane.vertex_normals[0] = (t_vec3){0, 1, 0};
	plane.vertex_normals[1] = (t_vec3){0, 1, 0};
	plane.vertex_normals[2] = (t_vec3){0, 1, 0};
	plane.vertex_normals[3] = (t_vec3){0, 1, 0};

// polygon 1
	plane.indices[0] = 0;
	plane.indices[1] = 1;
	plane.indices[2] = 2;
// polygon 2
	plane.indices[3] = 0;
	plane.indices[4] = 2;
	plane.indices[5] = 3;

	plane.n_vertices = 4;
	plane.n_indices = 6;
	plane.n_triangles = 2; // 생각해보니 무조건 indices / 3 아닌가?

	return (plane);
}

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

int	dummy_scene(t_scene *scene)
{
	const int n_meshs = 2;
	const int n_objects = 4;
	scene->n_meshs = n_meshs;
	scene->n_objects = n_objects;
	//scene->mesh = malloc(sizeof(t_object) * n_meshs);
	scene->objects = malloc(sizeof(t_object) * n_objects);

	scene->meshs[0] = mesh_plane();
	cylinder_init(&scene->meshs[1], 10);
	scene->objects[0] = dummy_object(&scene->meshs[0], (t_vec3){0, 0, 1});

	scene->objects[1] = dummy_object(&scene->meshs[1], (t_vec3){0, 1, 0});
	scene->objects[1].position = (t_vec3){-2, 4, 0};

	scene->objects[2] = dummy_object(&scene->meshs[1], (t_vec3){0, 1, 0});
	scene->objects[2].position = (t_vec3){0, 2, 0};

	scene->objects[3] = dummy_object(&scene->meshs[1], (t_vec3){0, 1, 0});
	scene->objects[3].position = (t_vec3){2, 1, 0};
	// TODO: scale 행렬 확인

	// sphere_init(&scene->meshs[1], 20, 20);
	// cylinder_init(&scene->meshs[2], 10);
	// scene->objects[0] = dummy_object(&scene->meshs[0], (t_vec3){0, 0, 1});
	// scene->objects[1] = dummy_object(&scene->meshs[1], (t_vec3){1, 0, 0});
	// scene->objects[1].position = (t_vec3){0, 1, 0};
	// scene->objects[2] = dummy_object(&scene->meshs[2], (t_vec3){0, 1, 0});
	// scene->objects[2].position = (t_vec3){0, 1, 0};


	// printf("%d\n",scene->meshs[0].n_vertices);

	scene->camera.eye = (t_vec3){0, 2, -5};
	// scene->camera.look_at = (t_vec3){0, 3, 1};
	// scene->camera.up = (t_vec3){0, 1, 0};
	// scene->camera.fov = 100;

	scene->light.position = (t_vec3){-2, 4, 0};
	scene->light.color = (t_vec3){3, 3, 3};
	// scene->light.color = (t_vec3){1, 1, 1};

	scene->ambient_light = (t_vec3){0.3, 0.3, 0.3};
	return (0);
}
