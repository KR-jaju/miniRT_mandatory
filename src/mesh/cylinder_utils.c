#include "mesh.h"

/*
yaw(y축 기준 회전)값과 y값을 받아 해당하는 좌표를 구함
매개변수 yaw는 라디안 단위로 들어옴.
실린더 중심을 기준으로 좌표를 구하기 위해, y값은 실린더 높이의 절반이 됨
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
