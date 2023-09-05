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

float	vec4_length(t_vec4 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

t_vec4	vec4_normalize(t_vec4 v)
{
	const float	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);

	return (vec4(v.x / length, v.y / length, v.z / length, v.w / length));
}
