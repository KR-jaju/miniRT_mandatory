#include "libmath.h"
#include <stdlib.h>

/*
동차좌표계에서
w = 1 -> 위치
w = 0 -> 방향벡터
*/
t_vec4	homogenize_pos(t_vec3 v)
{
	return ((t_vec4){v.x, v.y, v.z, 1});
}

t_vec4	homogenize_dir(t_vec3 v)
{
	return ((t_vec4){v.x, v.y, v.z, 0});
}

t_vec3	dehomogenize_pos(t_vec4 v)
{
	if (v.w != 1)
		exit(1);
	return ((t_vec3){v.x, v.y, v.z});
}

t_vec3	dehomogenize_dir(t_vec4 v)
{
	if (v.w != 0)
		exit(1);
	return ((t_vec3){v.x, v.y, v.z});
}
