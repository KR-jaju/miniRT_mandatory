/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:16 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:17 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mesh.h"
#include "settings.h"

void	plane_fill_vertices(t_vec3 *vertices)
{
	vertices[0] = (t_vec3){(float)-PLANE_SIDE_LENGTH / 2, \
							0, (float)PLANE_SIDE_LENGTH / 2};
	vertices[1] = (t_vec3){(float)-PLANE_SIDE_LENGTH / 2, \
							0, (float)-PLANE_SIDE_LENGTH / 2};
	vertices[2] = (t_vec3){(float)PLANE_SIDE_LENGTH / 2, \
							0, (float)-PLANE_SIDE_LENGTH / 2};
	vertices[3] = (t_vec3){(float)PLANE_SIDE_LENGTH / 2, \
							0, (float)PLANE_SIDE_LENGTH / 2};
}

void	plane_fill_indices(int *indices)
{
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 0;
	indices[4] = 2;
	indices[5] = 3;
}

void	plane_fill_vertex_normals(t_vec3 *vertex_normals)
{
	vertex_normals[0] = (t_vec3){0, 1, 0};
	vertex_normals[1] = (t_vec3){0, 1, 0};
	vertex_normals[2] = (t_vec3){0, 1, 0};
	vertex_normals[3] = (t_vec3){0, 1, 0};
}

void	plane_init(t_mesh *mesh)
{
	mesh->n_triangles = 2;
	mesh->n_vertices = 4;
	mesh->n_indices = mesh->n_triangles * 3;
	mesh->vertices = malloc(sizeof(t_vec3) * mesh->n_vertices);
	mesh->indices = malloc(sizeof(t_vec3) * mesh->n_indices);
	mesh->vertex_normals = malloc(sizeof(t_vec3) * mesh->n_vertices);
	plane_fill_vertices(mesh->vertices);
	plane_fill_indices(mesh->indices);
	plane_fill_vertex_normals(mesh->vertex_normals);
}
