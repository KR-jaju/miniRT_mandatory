#include "scene.h"

t_mat4	model_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale);
t_mat4	rotate_matrix(t_vec3 r);

static t_triangle	nth_triangle(int nth, \
								t_vec3 *vertices, t_vec3 *normals, int *indices)
{
	t_triangle	tri;
	const int	idx[3] = {indices[nth * 3], \
						indices[nth * 3 + 1], \
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

void	fill_triangles(t_object *object)
{
	int	i;

	i = 0;
	while (i < object->mesh->n_triangles)
	{
		object->triangles[i] = nth_triangle(i, object->vertices, \
								object->vertex_normals, object->mesh->indices);
		i++;
	}
}

void	fill_normals(t_object *object)
{
	const t_mat4	r_m = rotate_matrix(object->rotation);
	t_vec3			v3;
	t_vec4			v4;
	int				i;

	i = 0;
	while (i < object->mesh->n_vertices)
	{
		v3 = object->mesh->vertex_normals[i];
		v4 = mat4_mulmv(r_m, (t_vec4){v3.x, v3.y, v3.z, 0});
		object->vertex_normals[i] = vec3_normalize((t_vec3){v4.x, v4.y, v4.z});
		i++;
	}
}

void	fill_vertices(t_object *object)
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
