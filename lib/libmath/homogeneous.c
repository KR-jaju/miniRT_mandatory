#include "libmath.h"
#include <stdlib.h>

t_vec4	homogenize(t_vec3 v)
{
	return ((t_vec4){v.x, v.y, v.z, 1});
}

t_vec3	dehomogenize(t_vec4 v)
{
	if (v.w != 1)
		exit(1);
	return ((t_vec3){v.x, v.y, v.z});
}
