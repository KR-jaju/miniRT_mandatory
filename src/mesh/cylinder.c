/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:15 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:16 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "mesh.h"

void	cylinder_fill_vertices(t_vec3 *vertices, int sectors);
void	cylinder_fill_indices(int *indices, int sectors);

static void	cylinder_fill_vertex_normals(t_vec3 *vertex_normals, \
										t_vec3 *vertices, int sectors)
{
	int	i;

	vertex_normals[0] = (t_vec3){0, 1, 0};
	i = 0;
	while (i < sectors)
	{
		vertex_normals[i + 1] = (t_vec3){0, 1, 0};
		vertex_normals[i + 1 + sectors] = (t_vec3){0, -1, 0};
		vertex_normals[i + 1 + sectors * 2] = vec3_normalize(\
							(vec3_sub(vertices[i + 1], (t_vec3){0, 0.5, 0})));
		vertex_normals[i + 1 + sectors * 3] = vec3_normalize(\
				(vec3_sub(vertices[i + 1 + sectors], (t_vec3){0, -0.5, 0})));
		i++;
	}
	vertex_normals[sectors * 4 + 1] = (t_vec3){0, -1, 0};
}

/*
실린더는 다른 다면체와는 다르게 버텍스 버퍼가 두 배 필요하니 유의. (뚜껑과 옆면 따로 다루어야함)
*/
void	cylinder_init(t_mesh *mesh, int sectors)
{
	mesh->n_triangles = sectors * 4;
	mesh->n_vertices = (sectors * 4) + 2;
	mesh->n_indices = mesh->n_triangles * 3;
	mesh->vertices = malloc(sizeof(t_vec3) * mesh->n_vertices);
	mesh->indices = malloc(sizeof(t_vec3) * mesh->n_indices);
	mesh->vertex_normals = malloc(sizeof(t_vec3) * mesh->n_vertices);
	cylinder_fill_vertices(mesh->vertices, sectors);
	cylinder_fill_indices(mesh->indices, sectors);
	cylinder_fill_vertex_normals(mesh->vertex_normals, mesh->vertices, sectors);
}
