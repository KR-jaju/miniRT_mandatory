#include "libmath.h"

t_vec4	mat4_mulmv(t_mat4 m, t_vec4 v)
{
	t_vec4	mv;

	mv.x = (v.x * m.e[0][0]) + (v.y * m.e[1][0]) + \
			(v.z * m.e[2][0]) + (v.w * m.e[3][0]);
	mv.y = (v.x * m.e[0][1]) + (v.y * m.e[1][1]) + \
			(v.z * m.e[2][1]) + (v.w * m.e[3][1]);
	mv.z = (v.x * m.e[0][2]) + (v.y * m.e[1][2]) + \
			(v.z * m.e[2][2]) + (v.w * m.e[3][2]);
	mv.w = (v.x * m.e[0][3]) + (v.y * m.e[1][3]) + \
			(v.z * m.e[2][3]) + (v.w * m.e[3][3]);
	return (mv);
}
