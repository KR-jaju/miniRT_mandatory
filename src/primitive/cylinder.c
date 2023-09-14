// TODO: 변경된 구조체 구성 반영
// #include "primitive.h"
// #include <math.h>
// #include "libds.h"

// #define PI 3.14159f

// static
// t_vec3	point_at(float yaw, float y)
// {
// 	const float	sin_yaw = sin(yaw * PI / 180);
// 	const float	cos_yaw = sin(yaw * PI / 180);

// 	return ((t_vec3){
// 		sin_yaw,
// 		y,
// 		cos_yaw
// 	});
// }

// static
// void	add_wall(t_list *triangles, t_vec3 *vertices)
// {
// 	t_vec3	normal;

// 	normal = vec3_add(
// 			vec3_add(vertices[0], vertices[1]),
// 			vec3_add(vertices[2], vertices[3]));
// 	normal = vec3_mul(normal, 1 / vec3_length(normal));
// 	list_push(triangles, &(t_polygon){
// 		.vertex[0] = vertices[0],
// 		.vertex[1] = vertices[2],
// 		.vertex[2] = vertices[1],
// 		.normal = normal
// 	});
// 	list_push(triangles, &(t_polygon){
// 		.vertex[0] = vertices[1],
// 		.vertex[1] = vertices[2],
// 		.vertex[2] = vertices[3],
// 		.normal = normal
// 	});
// }

// static
// void	add_base(t_list *triangles, t_vec3 *vertices)
// {
// 	list_push(triangles, &(t_polygon){
// 		.vertex[0] = (t_vec3){0.0f, -1.0f, 0.0f},
// 		.vertex[1] = vertices[3],
// 		.vertex[2] = vertices[2],
// 		.normal = (t_vec3){0.0f, -1.0f, 0.0f}
// 	});
// 	list_push(triangles, &(t_polygon){
// 		.vertex[0] = vertices[0],
// 		.vertex[1] = vertices[1],
// 		.vertex[2] = (t_vec3){0.0f, 1.0f, 0.0f},
// 		.normal = (t_vec3){0.0f, 1.0f, 0.0f}
// 	});
// }

// static
// void	add_polygons(t_list *triangles, t_vec3 *vertices)
// {
// 	add_base(triangles, vertices);
// 	add_wall(triangles, vertices);
// }

// void	cylinder_init(t_mesh *mesh, uint32_t sectors)
// {
// 	t_list		triangles;
// 	const float	d_sector = 2 * PI / sectors;
// 	uint32_t	i;

// 	i = 0;
// 	while (i < sectors)
// 	{
// 		add_polygons(&triangles, (t_vec3 []){
// 			point_at(i * d_sector, 1),
// 			point_at((i + 1) * d_sector, 1),
// 			point_at(i * d_sector, -1),
// 			point_at((i + 1) * d_sector, -1),
// 		});
// 		i++;
// 	}
// 	mesh->polygons = list_collect(&triangles, &mesh->n_polygons);
// 	//TODO: free list
// }
