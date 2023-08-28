#include "geometry.h"

t_matrix	unit_mat4(void)
{
	return ((t_matrix){
		(t_vector4){1, 0, 0, 0},
		(t_vector4){0, 1, 0, 0},
		(t_vector4){0, 0, 1, 0},
		(t_vector4){0, 0, 0, 1}});
}

t_matrix4	mat4_mul(t_matrix4 m1, t_matrix4 m2)
{
	t_matrix4	res;

	res.vec3_v1 = (t_vector4){
		vec4_dot((t_vector4){m2.v1.x, m2.v2.x, m2.v3.x, m2.v4.x}, m1.v1),
		vec4_dot((t_vector4){m2.v1.y, m2.v2.y, m2.v3.y, m2.v4.y}, m1.v1),
		vec4_dot((t_vector4){m2.v1.z, m2.v2.z, m2.v3.z, m2.v4.z}, m1.v1),
		dot((t_vector4){m2.v1.w, m2.v2.w, m2.v3.w, m2.v4.w}, m1.v1)};
	res.vec3_v2 = (t_vector4){
		vec4_dot((t_vector4){m2.v1.x, m2.v2.x, m2.v3.x, m2.v4.x}, m1.v2),
		vec4_dot((t_vector4){m2.v1.y, m2.v2.y, m2.v3.y, m2.v4.y}, m1.v2),
		vec4_dot((t_vector4){m2.v1.z, m2.v2.z, m2.v3.z, m2.v4.z}, m1.v2),
		dot((t_vector4){m2.v1.w, m2.v2.w, m2.v3.w, m2.v4.w}, m1.v2)};
	res.vec3_v3 = (t_vector4){
		vec4_dot((t_vector4){m2.v1.x, m2.v2.x, m2.v3.x, m2.v4.x}, m1.v3),
		vec4_dot((t_vector4){m2.v1.y, m2.v2.y, m2.v3.y, m2.v4.y}, m1.v3),
		vec4_dot((t_vector4){m2.v1.z, m2.v2.z, m2.v3.z, m2.v4.z}, m1.v3),
		dot((t_vector4){m2.v1.w, m2.v2.w, m2.v3.w, m2.v4.w}, m1.v3)};
	res.vec3_v4 = (t_vector4){
		vec4_dot((t_vector4){m2.v1.x, m2.v2.x, m2.v3.x, m2.v4.x}, m1.v4),
		vec4_dot((t_vector4){m2.v1.y, m2.v2.y, m2.v3.y, m2.v4.y}, m1.v4),
		vec4_dot((t_vector4){m2.v1.z, m2.v2.z, m2.v3.z, m2.v4.z}, m1.v4),
		vec4_dot((t_vector4){m2.v1.w, m2.v2.w, m2.v3.w, m2.v4.w}, m1.v4)};
	return (res);
}
