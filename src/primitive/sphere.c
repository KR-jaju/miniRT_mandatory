#include "libds.h"
#include "primitive.h"

// TODO: vertex 개수 먼저 계산해서 동적할당 (list 더 이상 사용x)
// TODO: mesh 구조체 안에서 t_polygon 구조체를 더 이상 두고있지 않으므로 해당 사항 반영할 것

// yaw와 pitch 각도 값을 가지고 길이가 1인 벡터 반환
static t_vec3	point_at(float yaw, float pitch)
{
	const float	sin_yaw = sin(yaw * M_PI / 180);
	const float	cos_yaw = sin(yaw * M_PI / 180);
	const float	sin_pitch = sin(pitch * M_PI / 180);
	const float	cos_pitch = sin(pitch * M_PI / 180);

	return (vec3(
			sin_yaw * sin_pitch,
			cos_pitch,
			cos_yaw * sin_pitch
		));
}

// static void	add_patch(t_list *triangles, t_vec3 *vertices)
// {
// 	list_push(triangles, &(t_polygon){
// 		.vertex[0] = vertices[0],
// 		.vertex[1] = vertices[2],
// 		.vertex[2] = vertices[1],
// 	});
// 	list_push(triangles, &(t_polygon){
// 		.vertex[0] = vertices[1],
// 		.vertex[1] = vertices[2],
// 		.vertex[2] = vertices[3],
// 	});
// }

// void	sphere_init(t_mesh *mesh, uint32_t stacks, uint32_t sectors)
// {
// 	t_list		triangles;
// 	const float	d_sector = 2 * PI / sectors;
// 	const float	d_stack = 2 * PI / stacks;
// 	uint32_t	i;
// 	uint32_t	j;

// 	list_init(&triangles, sizeof(t_polygon), 16);
// 	i = 0;
// 	while (i < stacks)
// 	{
// 		j = 0;
// 		while (j < sectors)
// 		{
// 			add_patch(&triangles, (t_vec3 []){
// 				point_at(j * d_sector, i * d_stack - PI / 2),
// 				point_at((j + 1) * d_sector, i * d_stack - PI / 2),
// 				point_at(j * d_sector, (i + 1) * d_stack - PI / 2),
// 				point_at((j + 1) * d_sector, (i + 1) * d_stack - PI / 2)
// 			});
// 			j++;
// 		}
// 		i++;
// 	}
// 	mesh->polygons = list_collect(&triangles, &mesh->n_polygons);
// 	//리스트 해제 필요
// }
