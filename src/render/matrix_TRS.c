#include "render.h"
#include "libft.h"

t_mat4	translate_matrix(t_vec3 t)
{
	const float	values[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		t.x, t.y, t.z, 1
	};
	t_mat4		m;

	ft_memcpy(&m, values, sizeof(m));
	return (m);
}

// 왼손 좌표계이므로 z, y, x 순서로 적용 (yaw-pitch-roll)
t_mat4	rotate_matrix(t_vec3 r)
{
	const float	radian = M_PI / 180;
	const float	values_x[16] = {
		1, 0, 0, 0,
		0, cos(r.x * radian), sin(r.x * radian), 0,
		0, -sin(r.x * radian), cos(r.x * radian), 0,
		0, 0, 0, 1
	};
	const float	values_y[16] = {
		cos(r.y * radian), 0, -sin(r.y * radian), 0,
		0, 1, 0, 0,
		sin(r.y * radian), 0, cos(r.y * radian), 0,
		0, 0, 0, 1
	};
	const float	values_z[16] = {
		cos(r.z * radian), sin(r.z * radian), 0, 0,
		-sin(r.z * radian), cos(r.z * radian), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return (mat4_mulmm(values_mat4(values_x), \
				mat4_mulmm(values_mat4(values_y), \
							values_mat4(values_z))));
}

t_mat4	scale_matrix(t_vec3 s)
{
	const float	values[16] = {
		s.x, 0, 0, 0,
		0, s.y, 0, 0,
		0, 0, s.z, 0,
		0, 0, 0, 1
	};
	t_mat4		m;

	ft_memcpy(&m, values, sizeof(m));
	return (m);
}
