#ifndef MESH_H
# define MESH_H

# include <stdint.h>
# include <math.h>
# include "libmath.h"

/* ---------------------------- MACRO CONSTANTS ----------------------------- */

enum	e_mesh_type
{
	MESH_SPHERE = 0,
	MESH_PLANE,
	MESH_CYLINDER
};

# define MESH_COUNT 3

/* ------------------------ USER DEFINED DATA TYPES ------------------------- */

typedef struct s_mesh
{
	t_vec3		*vertices;
	t_vec3		*vertex_normals;
	int			*indices;
	int			n_vertices;
	int			n_indices;
	int			n_triangles;
}t_mesh;

/* --------------------------- FUNCTION PROTOTYPES -------------------------- */

void	sphere_init(t_mesh *mesh, int stacks, int sectors);
void	cylinder_init(t_mesh *mesh, int sectors);
void	plane_init(t_mesh *mesh);

#endif
