#include "scene.h"
#include "settings.h"

t_mat4	rotate_matrix(t_vec3 r);
t_mat4	model_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale);

static t_material	default_material(t_vec3 color)
{
	static t_material	material = {\
									(t_vec3){0, 0, 0}, \
									REFLECTIVITY, \
									K_DIFFUSE, \
									K_SPECULAR, \
									SHININESS, \
									};

	material.color = color;
	return (material);
}

static t_triangle	preprocess_nth_triangle(int nth, \
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

static t_vec3	preprocess_vertex(t_vec3 v, const t_mat4 *trs_mat)
{
	t_vec4	homo_v;

	homo_v = mat4_mulmv(*trs_mat, (t_vec4){v.x, v.y, v.z, 1});
	return ((t_vec3){homo_v.x, homo_v.y, homo_v.z});
}

static t_vec3	preprocess_vertex_normal(t_vec3 vn, const t_mat4 *r_mat)
{
	t_vec4	homo_vn;

	homo_vn = mat4_mulmv(*r_mat, (t_vec4){vn.x, vn.y, vn.z, 0});
	return (vec3_normalize((t_vec3){homo_vn.x, homo_vn.y, homo_vn.z}));
}

void	preprocess_object(t_object *obj)
{
	const t_mat4	r_mat = rotate_matrix(obj->rotation);
	const t_mat4	trs_mat = model_matrix(\
							obj->position, obj->rotation, obj->scale);
	int				i;

	i = 0;
	while (i < obj->mesh->n_vertices)
	{
		obj->vertices[i] = preprocess_vertex(obj->mesh->vertices[i], &trs_mat);
		obj->vertex_normals[i] = \
				preprocess_vertex_normal(obj->mesh->vertex_normals[i], &r_mat);
		i++;
	}
	i = 0;
	while (i < obj->mesh->n_triangles)
	{
		obj->triangles[i] = preprocess_nth_triangle(i, obj->vertices, \
								obj->vertex_normals, obj->mesh->indices);
		i++;
	}
	obj->material = default_material(obj->material.color);
}
