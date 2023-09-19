#ifndef MESH_H
# define MESH_H

# include <stdint.h>
# include <math.h>
# include "scene.h"

void	sphere_init(t_mesh *mesh, int stacks, int sectors);
void	cylinder_init(t_mesh *mesh, int sectors);
void	plane_init(t_mesh *mesh);

#endif
