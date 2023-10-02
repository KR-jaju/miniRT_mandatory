#include <stdlib.h>
#include "scene.h"
#include "settings.h"

t_mat4	rotate_matrix(t_vec3 r);
t_mat4	model_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale);
void	preprocess_vertices(t_vec3 *mesh_v_arr, t_vec3 *obj_v_arr, \
							const t_mat4 *trs_mat, int n_vertices);
t_vec3	preprocess_vertex_normals(t_vec3 *mesh_vn_arr, t_vec3 *obj_vn_arr, \
									const t_mat4 *r_mat, int n_vertices);
void	preprocess_triangles(t_triangle *tri_arr, \
								t_vec3 *vertices, t_vec3 *vertex_normals, \
								t_mesh *mesh);

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

/*
Based on the transform information (translate, rotation, scale) and
original model(mesh) stored in the object, the array of transformed vertices,
vertex normal, and triangles is obtained and filled in advance.
*/
int	preprocess_object(t_object *obj)
{
	const t_mat4	r_mat = rotate_matrix(obj->rotation);
	const t_mat4	trs_mat = model_matrix(\
							obj->position, obj->rotation, obj->scale);

	obj->vertices = malloc(sizeof(t_vec3) * obj->mesh->n_vertices);
	obj->vertex_normals = malloc(sizeof(t_vec3) * obj->mesh->n_vertices);
	obj->triangles = malloc(sizeof(t_triangle) * obj->mesh->n_triangles);
	if (!obj->vertices || !obj->vertex_normals || !obj->triangles)
		return (-1);
	preprocess_vertices(obj->mesh->vertices, obj->vertices, \
						&trs_mat, obj->mesh->n_vertices);
	preprocess_vertex_normals(obj->mesh->vertex_normals, obj->vertex_normals, \
						&r_mat, obj->mesh->n_vertices);
	preprocess_triangles(obj->triangles, \
						obj->vertices, obj->vertex_normals, obj->mesh);
	obj->material = default_material(obj->material.color);
	return (0);
}
