#include "libds.h"
#include "primitive.h"

/*
yaw(y축)와 pitch(x축) 각도 값을 가지고 길이가 1인 벡터 반환.
매개변수 yaw와 pitch는 라디안 단위로 들어옴.
	yaw 범위: 0 ~ 2pi (0 ~ 360도)
	pitch 범위: -pi ~ pi (-90 ~ 90도)
*/
static t_vec3	point_at(float yaw, float pitch)
{
	const float	sin_yaw = sin(yaw);
	const float	cos_yaw = sin(yaw);
	const float	sin_pitch = sin(pitch);
	const float	cos_pitch = sin(pitch);

	return (vec3(
			sin_yaw * sin_pitch,
			cos_pitch,
			cos_yaw * sin_pitch
		));
}

static void	fill_vertices(t_vec3 *vertices, int stacks, int sectors)
{
	const int	n_vertices = sectors * (stacks - 1) + 2;
	const float	d_sector = 2 * M_PI / sectors;
	const float	d_stack = M_PI / stacks;
	int			i;
	int			j;

	i = 0;
	vertices[0] = point_at(0, M_PI / 2);
	while (i < stacks - 1)
	{
		j = 0;
		while (j < sectors)
		{
			vertices[(i * sectors) + j + 1] = \
					point_at(d_sector * j, d_stack * i - M_PI / 2);
			j++;
		}
		i++;
	}
	vertices[n_vertices - 1] = point_at(0, -M_PI / 2);
}

static void	fill_indices_top_bottom(int *indices, \
									int stacks, int sectors, int *idx)
{
	const int	n_vertices = sectors * (stacks - 1) + 2;
	int			i;

	i = 0;
	while (i < sectors)
	{
		indices[(*idx)++] = 0;
		indices[(*idx)++] = i;
		indices[(*idx)++] = i + 1;
		indices[(*idx)++] = sectors * (stacks - 1) + i;
		indices[(*idx)++] = n_vertices - 1;
		indices[(*idx)++] = sectors * (stacks - 1) + i + 1;
		i++;
	}
}

static void	fill_indices(int *indices, int stacks, int sectors)
{
	int	idx;
	int	cur;
	int	i;
	int	j;

	idx = 0;
	fill_indices_top_bottom(indices, stacks, sectors, &idx);
	i = 0;
	while (i < stacks - 1)
	{
		j = 0;
		while (j < sectors)
		{
			cur = j + i * sectors;
			indices[idx++] = cur;
			indices[idx++] = cur + sectors;
			indices[idx++] = cur + 1;
			indices[idx++] = cur + 1;
			indices[idx++] = cur + sectors;
			indices[idx++] = cur + sectors + 1;
			j++;
		}
		i++;
	}
}

void	sphere_init(t_mesh *mesh, int stacks, int sectors)
{
	const int n_polygons = (2 * stacks * (sectors - 2)) + (2 * sectors);

	mesh->n_polygons = n_polygons; // TODO: 없앨지 검토 필요
	mesh->n_vertices = sectors * (stacks - 1) + 2;
	mesh->n_indices = n_polygons * 3;
	mesh->vertices = malloc(sizeof(t_vec3) * mesh->n_vertices);
	mesh->indices = malloc(sizeof(t_vec3) * mesh->n_indices);

	fill_vertices(mesh->vertices, stacks, sectors);
	fill_indices(mesh->indices, stacks, sectors);
	// fill_normals(mesh->normals, stacks, sectors); // TODO: 정점 노말 구하기
}
