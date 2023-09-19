#include "libds.h"
#include "mesh.h"
#include "debug.h"

/*
yaw(y축)와 pitch(x축) 각도 값을 가지고 길이가 1인 벡터 반환.
매개변수 yaw와 pitch는 라디안 단위로 들어옴.
	yaw 범위: 0 ~ 2pi (0 ~ 360도)
	pitch 범위: -pi ~ pi (-90 ~ 90도)
*/
static t_vec3	point_at(float yaw, float pitch)
{
	const float	sin_yaw = sin(yaw);
	const float	cos_yaw = cos(yaw);
	const float	sin_pitch = sin(pitch);
	const float	cos_pitch = cos(pitch);

	return (vec3(
			cos_pitch * cos_yaw,
			sin_pitch,
			cos_pitch * sin_yaw
		));
}

static void	fill_vertices(t_vec3 *vertices, int stacks, int sectors)
{
	const int	n_vertices = sectors * (stacks - 1) + 2;
	const float	d_sector = 2 * M_PI / sectors;
	const float	d_stack = M_PI / stacks;
	int			i;
	int			j;

	vertices[0] = point_at(0, M_PI / 2);
	i = 0;
	while (i < stacks - 1)
	{
		j = 0;
		while (j < sectors)
		{
			vertices[(i * sectors) + j + 1] = \
					point_at(d_sector * j, M_PI / 2 - d_stack * (i + 1));
			j++;
		}
		i++;
	}
	vertices[n_vertices - 1] = point_at(0, -M_PI / 2);
}

static void	fill_indices_caps(int *indices, int stacks, int sectors, int *idx)
{
	const int	last = sectors * (stacks - 1) + 1;
	int			i;

	i = 0;
	while (i < sectors)
	{
		indices[(*idx)++] = 0;
		indices[(*idx)++] = i + 1;
		indices[(*idx)++] = i + 2;
		indices[(*idx)++] = sectors * (stacks - 2) + 1 + i;
		indices[(*idx)++] = sectors * (stacks - 2) + 2 + i;
		indices[(*idx)++] = last;
		i++;
	}
	indices[*idx - 4] = 1;
	indices[(*idx) - 2] = sectors * (stacks - 2) + 1;
}

static void	fill_indices(int *indices, int stacks, int sectors)
{
	int	idx;
	int	cur;
	int	i;
	int	j;

	idx = 0;
	fill_indices_caps(indices, stacks, sectors, &idx);
	i = -1;
	while (++i < stacks - 2)
	{
		j = -1;
		while (++j < sectors)
		{
			cur = j + i * sectors + 1;
			indices[idx++] = cur;
			indices[idx++] = cur + sectors;
			indices[idx++] = cur + 1;
			indices[idx++] = cur + 1;
			indices[idx++] = cur + sectors;
			indices[idx++] = cur + sectors + 1;
		}
		indices[idx - 4] = i * sectors + 1;
		indices[idx - 3] = i * sectors + 1;
		indices[idx - 1] = (i + 1) * sectors + 1;
	}
}

void	sphere_init(t_mesh *mesh, int stacks, int sectors)
{
	mesh->n_triangles = 2 * sectors * (stacks - 1);
	mesh->n_vertices = sectors * (stacks - 1) + 2;
	mesh->n_indices = mesh->n_triangles * 3;
	mesh->vertices = malloc(sizeof(t_vec3) * mesh->n_vertices);
	mesh->indices = malloc(sizeof(t_vec3) * mesh->n_indices);
	mesh->vertex_normals = malloc(sizeof(t_vec3) * mesh->n_vertices);
	fill_vertices(mesh->vertices, stacks, sectors);
	fill_indices(mesh->indices, stacks, sectors);
	ft_memcpy(mesh->vertex_normals, mesh->vertices, \
				(sizeof(t_vec3) * mesh->n_vertices));
}
