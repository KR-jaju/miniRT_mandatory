#include "mesh.h"
#include "libds.h"
#include "alloc.h"

// TODO: vertex 개수 먼저 계산해서 동적할당 (list 더 이상 사용x)
// TODO: mesh 구조체 안에서 t_polygon 구조체를 더 이상 두고있지 않으므로 해당 사항 반영할 것

// void	plane_init(t_mesh *mesh)
// {
// 	mesh->polygons = alloc(2 * sizeof(t_polygon));
// 	mesh->n_polygons = 2;
// 	mesh->polygons[0] = (t_polygon){
// 		.vertex[0] = vec3(-1, 0, 1),
// 		.vertex[1] = vec3(-1, 0, -1),
// 		.vertex[2] = vec3(1, 0, 1),
// 		.normal = vec3(0, 1, 0)
// 	};
// 	mesh->polygons[1] = (t_polygon){
// 		.vertex[0] = vec3(1, 0, 1),
// 		.vertex[1] = vec3(-1, 0, -1),
// 		.vertex[2] = vec3(1, 0, -1),
// 		.normal = vec3(0, 1, 0)
// 	};
// }