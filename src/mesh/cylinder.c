#include "mesh.h"
#include "libds.h"
#include "debug.h"

// wall, base

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
		cos_yaw,
		y,
		sin_yaw
	});
}

static void	fill_vertices(t_vec3 *vertices, int sectors)
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

// 윗 뚜껑은 위에서 아래로 봤을때 앞면(반시계방향), 아랫 뚜껑은 아래에서 위로 봤을때 앞면(반시계방향)
static void	fill_indices_caps(int *indices, int sectors, int *idx)
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

static void	fill_indices_side(int *indices, int sectors, int *idx)
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

static void	fill_indices(int *indices, int sectors)
{
	int	idx;

	idx = 0;
	fill_indices_caps(indices, sectors, &idx);
	fill_indices_side(indices, sectors, &idx);
}

static void	fill_vertex_normals(t_vec3 *vertex_normals, \
								t_vec3 *vertices, int sectors)
{
	int	i;

	vertex_normals[0] = (t_vec3){0, 1, 0};
	i = 0;
	while (i < sectors)
	{
		vertex_normals[i + 1] = (t_vec3){0, 1, 0};
		vertex_normals[i + 1 + sectors] = (t_vec3){0, -1, 0};
		vertex_normals[i + 1 + sectors * 2] = vec3_normalize((vec3_sub(vertices[i + 1], (t_vec3){0, 0.5, 0})));
		vertex_normals[i + 1 + sectors * 3] = vec3_normalize((vec3_sub(vertices[i + 1 + sectors], (t_vec3){0, -0.5, 0})));
		i++;
	}
	vertex_normals[sectors * 4 + 1] = (t_vec3){0, -1, 0};
}

/*
실린더의 정점 노말:
vertexNormal = normalize(vertexPosition - ringCenter)
*/
void	cylinder_init(t_mesh *mesh, int sectors)
{
	mesh->n_triangles = sectors * 4;
	mesh->n_vertices = (sectors * 4) + 2;
	mesh->n_indices = mesh->n_triangles * 3;
	mesh->vertices = malloc(sizeof(t_vec3) * mesh->n_vertices);
	mesh->indices = malloc(sizeof(t_vec3) * mesh->n_indices);
	mesh->vertex_normals = malloc(sizeof(t_vec3) * mesh->n_vertices);
	fill_vertices(mesh->vertices, sectors);
	fill_indices(mesh->indices, sectors);
	fill_vertex_normals(mesh->vertex_normals, mesh->vertices, sectors);

	for (int i = 0; i < mesh->n_vertices; i++)
	{
		printf("%dth vertex: ", i);
		print_vec3(mesh->vertices[i]);
	}
		for (int i = 0; i < mesh->n_vertices; i++)
	{
		printf("%dth normal: ", i);
		print_vec3(mesh->vertex_normals[i]);
	}
	for (int i = 0; i < mesh->n_triangles; i++)
	{
		printf("%dth polygon: %d %d %d\n", i, mesh->indices[i * 3], mesh->indices[i * 3 + 1], mesh->indices[i * 3 + 2]);
	}
}
