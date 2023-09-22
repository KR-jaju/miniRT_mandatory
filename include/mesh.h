#ifndef MESH_H
# define MESH_H

# include <stdint.h>
# include <math.h>
# include "scene.h"

enum	e_mesh_type
{
	MESH_SPHERE = 0,
	MESH_PLANE,
	MESH_CYLINDER
};

# define MESH_COUNT 3

void	sphere_init(t_mesh *mesh, int stacks, int sectors);
void	cylinder_init(t_mesh *mesh, int sectors);
void	plane_init(t_mesh *mesh);

#endif
