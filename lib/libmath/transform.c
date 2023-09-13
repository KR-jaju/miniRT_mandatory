#include "libmath.h"

t_vec4	mat4_mulmv(t_mat4 m, t_vec4 v)
{
	t_vec4	res;

	res.x = (v.x * m.v1.x) + (v.y * m.v2.x) + (v.z * m.v3.x) + (v.w * m.v4.x);
	res.y = (v.x * m.v1.y) + (v.y * m.v2.y) + (v.z * m.v3.y) + (v.w * m.v4.y);
	res.z = (v.x * m.v1.z) + (v.y * m.v2.z) + (v.z * m.v3.z) + (v.w * m.v4.z);
	res.w = (v.x * m.v1.w) + (v.y * m.v2.w) + (v.z * m.v3.w) + (v.w * m.v4.w);
	return (res);
}
