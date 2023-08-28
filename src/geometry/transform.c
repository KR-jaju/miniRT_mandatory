#include "geometry.h"

t_vector3	mat4_mul_vec3(t_matrix4 m, t_vector3 v)
{
	t_vector3	res;

	res.x = (v.x * m.v1.x) + (v.y * m.v2.x) + (v.z * m.v3.x) + m.v4.x;
	res.y = (v.x * m.v1.y) + (v.y * m.v2.y) + (v.z * m.v3.y) + m.v4.y;
	res.z = (v.x * m.v1.z) + (v.y * m.v2.z) + (v.z * m.v3.z) + m.v4.z;
	return (res);
}

t_vector4	mat4_mul_vec4(t_matrix4 m, t_vector4 v)
{
	t_vector4	res;

	res.x = (v.x * m.v1.x) + (v.y * m.v2.x) + (v.z * m.v3.x) + (v.w * m.v4.x);
	res.y = (v.x * m.v1.y) + (v.y * m.v2.y) + (v.z * m.v3.y) + (v.w * m.v4.y);
	res.z = (v.x * m.v1.z) + (v.y * m.v2.z) + (v.z * m.v3.z) + (v.w * m.v4.z);
	res.w = (v.x * m.v1.w) + (v.y * m.v2.w) + (v.z * m.v3.w) + (v.w * m.v4.w);
	return (res);
}

void	compose_scale_mat4(t_matrix4 *m, double x, double y, double z)
{
	const t_matrix	m_scale = (t_matrix){
		(t_vector4){x, 0, 0, 0},
		(t_vector4){0, y, 0, 0},
		(t_vector4){0, 0, z, 0},
		(t_vector4){0, 0, 0, 1}
	};

	*m = mat4_mul(*m, m_scale);
}

void	compose_rotate_mat4(t_matrix4 *m, double x, double y, double z)
{
	const double	radian = M_PI / 180;
	const t_matrix	m_rotate_x = (t_matrix){
		(t_vector4){1, 0, 0, 0},
		(t_vector4){0, cos(x * radian), sin(x * radian), 0},
		(t_vector4){0, -sin(x * radian), cos(x * radian), 0},
		(t_vector4){0, 0, 0, 1}
	};
	const t_matrix	m_rotate_y = (t_matrix){
		(t_vector4){cos(y * radian), 0, -sin(y * radian), 0},
		(t_vector4){0, 1, 0, 0},
		(t_vector4){sin(y * radian), 0, cos(y * radian), 0},
		(t_vector4){0, 0, 0, 1}
	};
	const t_matrix	m_rotate_z = (t_matrix){
		(t_vector4){cos(z * radian), sin(z * radian), 0, 0},
		(t_vector4){-sin(z * radian), cos(z * radian), 0, 0},
		(t_vector4){0, 0, 1, 0},
		(t_vector4){0, 0, 0, 1}
	};

	*m = mat4_mul(*m, m_rotate_x);
	*m = mat4_mul(*m, m_rotate_y);
	*m = mat4_mul(*m, m_rotate_z);
}

void	compose_move_mat4(t_matrix4 *m, double x, double y, double z)
{
	const t_matrix	m_move = (t_matrix){
		(t_vector4){1, 0, 0, 0},
		(t_vector4){0, 1, 0, 0},
		(t_vector4){0, 0, 1, 0},
		(t_vector4){x, y, z, 1}
	};

	*m = mat4_mul(*m, m_move);
}
