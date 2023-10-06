/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:32 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:33 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "settings.h"

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

void	preprocess_triangles(t_triangle *tri_arr, \
								t_vec3 *vertices, t_vec3 *vertex_normals, \
								t_mesh *mesh)
{
	int	i;

	i = 0;
	while (i < mesh->n_triangles)
	{
		tri_arr[i] = nth_triangle(i, vertices, vertex_normals, mesh->indices);
		i++;
	}
}

void	preprocess_vertices(t_vec3 *mesh_v_arr, t_vec3 *obj_v_arr, \
							const t_mat4 *trs_mat, int n_vertices)
{
	t_vec3	v;
	t_vec4	homo_v;
	int		i;

	i = 0;
	while (i < n_vertices)
	{
		v = mesh_v_arr[i];
		homo_v = mat4_mulmv(*trs_mat, (t_vec4){v.x, v.y, v.z, 1});
		obj_v_arr[i] = (t_vec3){homo_v.x, homo_v.y, homo_v.z};
		i++;
	}
}

void	preprocess_vertex_normals(t_vec3 *mesh_vn_arr, t_vec3 *obj_vn_arr, \
									const t_mat4 *r_mat, int n_vertices)
{
	t_vec3	vn;
	t_vec4	homo_vn;
	int		i;

	i = 0;
	while (i < n_vertices)
	{
		vn = mesh_vn_arr[i];
		homo_vn = mat4_mulmv(*r_mat, (t_vec4){vn.x, vn.y, vn.z, 0});
		obj_vn_arr[i] = (t_vec3){homo_vn.x, homo_vn.y, homo_vn.z};
		i++;
	}
}
