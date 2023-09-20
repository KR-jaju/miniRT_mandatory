#include "mesh.h"
#include "libds.h"

// TODO: vertex 개수 먼저 계산해서 동적할당 (list 더 이상 사용x)
// TODO: mesh 구조체 안에서 t_polygon 구조체를 더 이상 두고있지 않으므로 해당 사항 반영할 것

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
		i++;
	}
	i = 0;
	while (i < sectors)
	{
		vertices[i + sectors + 1] = point_at(d_sector * i, (float)-1 / 2);
		i++;
	}
	vertices[sectors * 2 + 1] = (t_vec3){0, -0.5, 0};
}

static void	fill_indices_caps(int *indices, int sectors, int *idx)
{
	const int	last = sectors * 2 + 1;
	int			i;

	i = 0;
	while (i < sectors)
	{
		indices[(*idx)++] = 0;
		indices[(*idx)++] = i + 1;
		indices[(*idx)++] = i + 2;
		indices[(*idx)++] = i + (sectors + 1);
		indices[(*idx)++] = i + (sectors + 2);
		indices[(*idx)++] = last;
		i++;
	}
	indices[*idx - 4] = 1;
	indices[(*idx) - 2] = sectors + 1;
}

static void	fill_indices_side(int *indices, int sectors, int *idx)
{
	int	i;

	i = 0;
	while (i < sectors)
	{
		indices[(*idx)++] = i + 1;
		indices[(*idx)++] = i + sectors + 1;
		indices[(*idx)++] = i + sectors + 2;
		indices[(*idx)++] = i + 2;
		indices[(*idx)++] = i + 1;
		indices[(*idx)++] = i + sectors + 2;
		i++;
	}
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
	while (i < sectors)
	{
		vertex_normals[i + 1] = vec3_normalize(\
								vec3_sub(vertices[i + 1], (t_vec3){0, 1, 0}));
		vertex_normals[sectors + i + 1] = vec3_normalize(\
						vec3_sub(vertices[sectors + i + 1], (t_vec3){0, 1, 0}));
		i++;
	}
	vertex_normals[sectors * 2 + 1] = (t_vec3){0, -1, 0};
}

/*
실린더의 정점 노말:
vertexNormal = normalize(vertexPosition - ringCenter)
*/
void	cylinder_init(t_mesh *mesh, int sectors)
{
	int	i;

	mesh->n_triangles = sectors * 4;
	mesh->n_vertices = sectors * 2 + 2;
	mesh->n_indices = mesh->n_triangles * 3;
	mesh->vertices = malloc(sizeof(t_vec3) * mesh->n_vertices);
	mesh->indices = malloc(sizeof(t_vec3) * mesh->n_indices);
	mesh->vertex_normals = malloc(sizeof(t_vec3) * mesh->n_vertices);
	fill_vertices(mesh->vertices, sectors);
	fill_indices(mesh->indices, sectors);
	fill_vertex_normals(mesh->vertex_normals, mesh->vertices, sectors);
}
