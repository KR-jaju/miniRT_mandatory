#include "libmath.h"

/*
입사벡터: 교차점 -> 빛
*/
t_vec3	incident_direction(t_vec3 hit_pos, t_vec3 light_pos)
{
	return (vec3_normalize(\
			vec3_sub(light_pos, hit_pos)));
}

/*
반사벡터: 입사각과 동일한 각도로 반사
	R = -i + 2n(i * n)
	i: 입사벡터, n: 교차점의 노말
*/
t_vec3	reflection_direction(t_vec3 i, t_vec3 n)
{
	return (vec3_normalize(\
			vec3_add(vec3_mul(i, -1), \
					vec3_mul(vec3_mul(n, vec3_dot(i, n)), 2))));
}

/*
시선벡터: 교차점 -> 카메라
*/
t_vec3	view_direction(t_vec3 camera_pos, t_vec3 hit_pos)
{
	return (vec3_normalize(\
			vec3_sub(camera_pos, hit_pos)));
}
