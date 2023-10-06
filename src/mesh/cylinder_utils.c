/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:13 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:14 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

/*
yaw와 y값을 받아 해당하는 좌표를 반환
- yaw 범위: [0, 2pi]
- |y| = 실린더 높이의 절반
- Disk(횡단면)의 중심으로부터 좌표까지의 길이 = 단위원의 반지름(0.5)
	(즉 x, z값만 따졌을 때 길이가 0.5)
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
