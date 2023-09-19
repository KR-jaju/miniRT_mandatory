#include <stdlib.h>
#include "libmath.h"
#include "scene.h"

t_mat4	model_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale);
t_mat4	rotate_matrix(t_vec3 r);

static t_triangle nth_triangle(int nth, \
							t_vec3 *vertices, t_vec3 *normals, int *indices)
{
	t_triangle	tri;
	const int	idx[3] = {indices[nth * 3],
							indices[nth * 3 + 1], 
							indices[nth * 3 + 2]};

	tri.vertices[0] = vertices[idx[0]];
	tri.vertices[1] = vertices[idx[1]];
	tri.vertices[2] = vertices[idx[2]];
	tri.vertex_normals[0] = normals[idx[0]];
	tri.vertex_normals[1] = normals[idx[1]];
	tri.vertex_normals[2] = normals[idx[2]];
	tri.face_normal = vec3_normalize(\
						vec3_cross(vec3_sub(tri.vertices[2], tri.vertices[0]), \
								vec3_sub(tri.vertices[1], tri.vertices[0])));
	return (tri);
}

static void	fill_triangles(t_object *object)
{
	int	i;

	i = 0;
	while (i < object->mesh->n_triangles)
	{
		object->triangles[i] = nth_triangle(i, object->vertices, \
									object->normals, object->mesh->indices);
		i++;
	}
}

static void	fill_normals(t_object *object)
{
	const t_mat4	r_m = rotate_matrix(object->rotation);
	t_vec3			v3;
	t_vec4			v4;
	int				i;

	i = 0;
	while (i < object->mesh->n_vertices)
	{
		v3 = object->mesh->normals[i];
		v4 = mat4_mulmv(r_m, (t_vec4){v3.x, v3.y, v3.z, 0});
		object->normals[i] = vec3_normalize((t_vec3){v4.x, v4.y, v4.z});
		i++;
	}
}

static void	fill_vertices(t_object *object)
{
	const t_mat4	trs_m = model_matrix(\
							object->position, object->rotation, object->scale);
	t_vec3			v3;
	t_vec4			v4;
	int				i;

	i = 0;
	while (i < object->mesh->n_vertices)
	{
		v3 = object->mesh->vertices[i];
		v4 = mat4_mulmv(trs_m, (t_vec4){v3.x, v3.y, v3.z, 1});
		object->vertices[i] = (t_vec3){v4.x, v4.y, v4.z};
		i++;
	}
}

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
		object->normals = malloc(sizeof(t_vec3) * object->mesh->n_vertices);
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
		fill_vertices(&scene->objects[i]);
		fill_normals(&scene->objects[i]);
		fill_triangles(&scene->objects[i]);
		i++;
	}
	// TODO: 카메라 행렬 여기서 구하기
	return (0);
}
