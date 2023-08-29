#include "libmath.h"

t_mat4	unit_mat4(void)
{
	return ((t_mat4){
		(t_vec4){1, 0, 0, 0},
		(t_vec4){0, 1, 0, 0},
		(t_vec4){0, 0, 1, 0},
		(t_vec4){0, 0, 0, 1}});
}

t_mat4	mat4_mul(t_mat4 m1, t_mat4 m2)
{
	t_mat4	res;

	res.v1 = (t_vec4){
		vec4_dot((t_vec4){m2.v1.x, m2.v2.x, m2.v3.x, m2.v4.x}, m1.v1),
		vec4_dot((t_vec4){m2.v1.y, m2.v2.y, m2.v3.y, m2.v4.y}, m1.v1),
		vec4_dot((t_vec4){m2.v1.z, m2.v2.z, m2.v3.z, m2.v4.z}, m1.v1),
		vec4_dot((t_vec4){m2.v1.w, m2.v2.w, m2.v3.w, m2.v4.w}, m1.v1)};
	res.v2 = (t_vec4){
		vec4_dot((t_vec4){m2.v1.x, m2.v2.x, m2.v3.x, m2.v4.x}, m1.v2),
		vec4_dot((t_vec4){m2.v1.y, m2.v2.y, m2.v3.y, m2.v4.y}, m1.v2),
		vec4_dot((t_vec4){m2.v1.z, m2.v2.z, m2.v3.z, m2.v4.z}, m1.v2),
		vec4_dot((t_vec4){m2.v1.w, m2.v2.w, m2.v3.w, m2.v4.w}, m1.v2)};
	res.v3 = (t_vec4){
		vec4_dot((t_vec4){m2.v1.x, m2.v2.x, m2.v3.x, m2.v4.x}, m1.v3),
		vec4_dot((t_vec4){m2.v1.y, m2.v2.y, m2.v3.y, m2.v4.y}, m1.v3),
		vec4_dot((t_vec4){m2.v1.z, m2.v2.z, m2.v3.z, m2.v4.z}, m1.v3),
		vec4_dot((t_vec4){m2.v1.w, m2.v2.w, m2.v3.w, m2.v4.w}, m1.v3)};
	res.v4 = (t_vec4){
		vec4_dot((t_vec4){m2.v1.x, m2.v2.x, m2.v3.x, m2.v4.x}, m1.v4),
		vec4_dot((t_vec4){m2.v1.y, m2.v2.y, m2.v3.y, m2.v4.y}, m1.v4),
		vec4_dot((t_vec4){m2.v1.z, m2.v2.z, m2.v3.z, m2.v4.z}, m1.v4),
		vec4_dot((t_vec4){m2.v1.w, m2.v2.w, m2.v3.w, m2.v4.w}, m1.v4)};
	return (res);
}
