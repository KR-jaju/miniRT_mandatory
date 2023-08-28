#include "geometry.h"

t_vector3	vec3(float x, float y, float z)
{
	return (vector3{x, y, z});
}

t_vector3	vec3_add(t_vector3 v1, t_vector3 v2)
{
	return (vector3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector3	vec3_sub(t_vector3 v1, t_vector3 v2)
{
	return (vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

float	vec3_dot(t_vector3 v1, t_vector3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector3	vec3_cross(t_vector3 v1, t_vector3 v2)
{
	t_vector3	res;

	res.x = v1.y * v2.z - v1.z * v2.y;
	res.y = v1.z * v2.x - v1.x * v2.z;
	res.z = v1.x * v2.y - v1.y * v2.x;
	return (res);
}

float	vec3_length(t_vector3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}
