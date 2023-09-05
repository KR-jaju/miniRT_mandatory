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

void	compose_scale_mat4(t_mat4 *m, float x, float y, float z)
{
	const t_mat4	m_scale = (t_mat4){
		(t_vec4){x, 0, 0, 0},
		(t_vec4){0, y, 0, 0},
		(t_vec4){0, 0, z, 0},
		(t_vec4){0, 0, 0, 1}
	};

	*m = mat4_mulmm(*m, m_scale);
}

void	compose_rotate_mat4(t_mat4 *m, float x, float y, float z)
{
	const float		radian = M_PI / 180;
	const t_mat4	m_rotate_x = (t_mat4){
		(t_vec4){1, 0, 0, 0},
		(t_vec4){0, cos(x * radian), sin(x * radian), 0},
		(t_vec4){0, -sin(x * radian), cos(x * radian), 0},
		(t_vec4){0, 0, 0, 1}
	};
	const t_mat4	m_rotate_y = (t_mat4){
		(t_vec4){cos(y * radian), 0, -sin(y * radian), 0},
		(t_vec4){0, 1, 0, 0},
		(t_vec4){sin(y * radian), 0, cos(y * radian), 0},
		(t_vec4){0, 0, 0, 1}
	};
	const t_mat4	m_rotate_z = (t_mat4){
		(t_vec4){cos(z * radian), sin(z * radian), 0, 0},
		(t_vec4){-sin(z * radian), cos(z * radian), 0, 0},
		(t_vec4){0, 0, 1, 0},
		(t_vec4){0, 0, 0, 1}
	};

	*m = mat4_mulmm(*m, m_rotate_x);
	*m = mat4_mulmm(*m, m_rotate_y);
	*m = mat4_mulmm(*m, m_rotate_z);
}

void	compose_move_mat4(t_mat4 *m, float x, float y, float z)
{
	const t_mat4	m_move = (t_mat4){
		(t_vec4){1, 0, 0, 0},
		(t_vec4){0, 1, 0, 0},
		(t_vec4){0, 0, 1, 0},
		(t_vec4){x, y, z, 1}
	};

	*m = mat4_mulmm(*m, m_move);
}
