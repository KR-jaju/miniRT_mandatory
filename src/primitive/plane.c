
#include "primitive.h"
#include <math.h>
#include "libds.h"
#include "alloc.h"

void	plane_init(t_mesh *mesh)
{
	mesh->polygons = alloc(2 * sizeof(t_polygon));
	mesh->n_polygons = 2;
	mesh->polygons[0] = (t_polygon){
		.vertex[0] = vec3(-1, 0, 1),
		.vertex[1] = vec3(-1, 0, -1),
		.vertex[2] = vec3(1, 0, 1),
		.normal = vec3(0, 1, 0)
	};
	mesh->polygons[1] = (t_polygon){
		.vertex[0] = vec3(1, 0, 1),
		.vertex[1] = vec3(-1, 0, -1),
		.vertex[2] = vec3(1, 0, -1),
		.normal = vec3(0, 1, 0)
	};
}
