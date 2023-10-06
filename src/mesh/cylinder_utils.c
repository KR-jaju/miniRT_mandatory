/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:13 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:36:51 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

/*
Receive yaw and y values and return the corresponding coordinates
- Yaw range: [0, 2pi]
- |y| = half the height of the cylinder
- Length from the center of the disk = radius of the unit circle (0.5)
	(i.e., the length is 0.5 when considering x and z values only)
*/
static t_vec3	point_at(float yaw, float y)
{
	const float	sin_yaw = sin(yaw);
	const float	cos_yaw = cos(yaw);

	return ((t_vec3){
		cos_yaw * 0.5f,
		y,
		sin_yaw * 0.5f
	});
}

void	cylinder_fill_vertices(t_vec3 *vertices, int sectors)
{
	const float	d_sector = 2 * M_PI / sectors;
	int			i;

	vertices[0] = (t_vec3){0, 0.5, 0};
	i = 0;
	while (i < sectors)
	{
		vertices[i + 1] = point_at(d_sector * i, (float)1 / 2);
		vertices[sectors + i + 1] = point_at(d_sector * i, (float)-1 / 2);
		vertices[sectors * 2 + i + 1] = vertices[i + 1];
		vertices[sectors * 3 + i + 1] = vertices[sectors + i + 1];
		i++;
	}
	vertices[sectors * 4 + 1] = (t_vec3){0, -0.5, 0};
}

static void	cylinder_fill_indices_caps(int *indices, int sectors, int *idx)
{
	const int	last = sectors * 4 + 1;
	int			i;

	i = 0;
	while (i < sectors)
	{
		indices[(*idx)++] = 0;
		indices[(*idx)++] = i + 1;
		indices[(*idx)++] = i + 2;
		indices[(*idx)++] = i + (sectors + 2);
		indices[(*idx)++] = i + (sectors + 1);
		indices[(*idx)++] = last;
		i++;
	}
	indices[*idx - 4] = 1;
	indices[(*idx) - 3] = sectors + 1;
}

static void	cylinder_fill_indices_side(int *indices, int sectors, int *idx)
{
	const int	offset = sectors * 2;
	int			i;

	i = 0;
	while (i < sectors)
	{
		indices[(*idx)++] = offset + i + 1;
		indices[(*idx)++] = offset + i + sectors + 1;
		indices[(*idx)++] = offset + i + sectors + 2;
		indices[(*idx)++] = offset + i + 2;
		indices[(*idx)++] = offset + i + 1;
		indices[(*idx)++] = offset + i + sectors + 2;
		i++;
	}
	indices[*idx - 4] = offset + sectors + 1;
	indices[*idx - 3] = offset + 1;
	indices[*idx - 2] = offset + sectors;
	indices[*idx - 1] = offset + sectors + 1;
}

void	cylinder_fill_indices(int *indices, int sectors)
{
	int	idx;

	idx = 0;
	cylinder_fill_indices_caps(indices, sectors, &idx);
	cylinder_fill_indices_side(indices, sectors, &idx);
}
