#include "libmath.h"

t_vec4	vec4(float x, float y, float z, float w)
{
	return ((t_vec4){x, y, z, w});
}

t_vec4	vec4_add(t_vec4 v1, t_vec4 v2)
{
	return (vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w));
}

t_vec4	vec4_sub(t_vec4 v1, t_vec4 v2)
{
	return (vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w));
}

t_vec4	vec4_mul(t_vec4 v, float a)
{
	return (vec4(v.x * a, v.y * a, v.z * a, v.w * a));
}

float	vec4_dot(t_vec4 v1, t_vec4 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w);
}
