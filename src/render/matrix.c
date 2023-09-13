#include "render.h"

t_mat4	translate_matrix(t_vec3 t)
{
	return ((t_mat4){
		(t_vec4){1, 0, 0, 0},
		(t_vec4){0, 1, 0, 0},
		(t_vec4){0, 0, 1, 0},
		(t_vec4){t.x, t.y, t.z, 1}
	});
}

// 왼손 좌표계이므로 z, y, x 순서로 적용 (yaw-pitch-roll)
t_mat4	rotate_matrix(t_vec3 r)
{
	const float		radian = M_PI / 180;
	const t_mat4	m_rotate_x = (t_mat4){
		(t_vec4){1, 0, 0, 0},
		(t_vec4){0, cos(r.x * radian), sin(r.x * radian), 0},
		(t_vec4){0, -sin(r.x * radian), cos(r.x * radian), 0},
		(t_vec4){0, 0, 0, 1}
	};
	const t_mat4	m_rotate_y = (t_mat4){
		(t_vec4){cos(r.y * radian), 0, -sin(r.y * radian), 0},
		(t_vec4){0, 1, 0, 0},
		(t_vec4){sin(r.y * radian), 0, cos(r.y * radian), 0},
		(t_vec4){0, 0, 0, 1}
	};
	const t_mat4	m_rotate_z = (t_mat4){
		(t_vec4){cos(r.z * radian), sin(r.z * radian), 0, 0},
		(t_vec4){-sin(r.z * radian), cos(r.z * radian), 0, 0},
		(t_vec4){0, 0, 1, 0},
		(t_vec4){0, 0, 0, 1}
	};

	return (mat4_mulmm(m_rotate_x, \
			mat4_mulmm(m_rotate_y, (mat4_mulmm(m_rotate_z, unit_mat4())))));
}

t_mat4	scale_matrix(t_vec3 s)
{
	return ((t_mat4){
		(t_vec4){s.x, 0, 0, 0},
		(t_vec4){0, s.y, 0, 0},
		(t_vec4){0, 0, s.z, 0},
		(t_vec4){0, 0, 0, 1}
	});
}

/*
로컬 공간 -> 월드 공간 매핑

T, R, S 세 개의 행렬을 compose하면 된다.
*/
t_mat4	model_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_mat4	t;
	t_mat4	r;
	t_mat4	s;

	t = translate_matrix(pos);
	r = rotate_matrix(rot);
	s = scale_matrix(scale);
	return (mat4_mulmm(t, mat4_mulmm(r, s)));
}

/*
월드 공간 -> 뷰 공간 매핑

뷰 공간은 카메라의 세 개의 방향벡터가 이루는 공간이므로,
이미 알고있는 카메라 방향벡터를 그대로 행벡터로 삼으면 된다.
세 개의 축이 직교하는 유클리드 공간끼리의 매핑이므로 간단하게 기저벡터의 전환으로 생각할 수 있다.
(right - x축, up - y축, forward - z축)

우리는 카메라 파라미터를 eye, look-at, up로 두고 있으므로
이 파라미터들을 이용해 view space의 basis 벡터(right, up, forward)를 구하면 된다.

뷰 공간으로 매핑하기 위해서는 먼저 중심을 카메라 기준으로 옮기고(이동변환), 그 다음 회전변환을 하면 된다.
뷰 행렬 = (회전 변환 행렬) * (이동 변환 행렬)
*/
t_mat4	view_matrix(t_vec3 eye, t_vec3 look_at, t_vec3 up)
{
	t_vec3	basis_right;
	t_vec3	basis_up;
	t_vec3	basis_forward;
	t_mat4	m_rotation;
	t_mat4	m_translation;

	basis_forward = vec3_normalize(vec3_sub(eye, look_at));
	basis_right = vec3_normalize(vec3_cross(up, basis_forward));
	basis_up = vec3_normalize(vec3_cross(basis_forward, basis_right));

	m_rotation.v1 = (t_vec4){basis_right.x, basis_up.x, basis_forward.x, 0};
	m_rotation.v2 = (t_vec4){basis_right.y, basis_up.y, basis_forward.y, 0};
	m_rotation.v3 = (t_vec4){basis_right.z, basis_up.z, basis_forward.z, 0};
	m_rotation.v4 = (t_vec4){0, 0, 0, 0};

	m_translation = unit_mat4();
	translate_matrix(vec3_mul(eye, -1), &m_translation);

	return (mat4_mulmm(m_rotation, m_translation));
}

/*
뷰 공간 -> 클립 공간 (NDC공간 아님, 정규화x)

투영 행렬을 구하기 위해 near, far가 필요한 것은 맞는데,
우리는 z버퍼를 사용하지 않으므로 아무값이나 설정해도 무방.
(기본값 0.3, 1000으로 설정할 예정)
*/
t_mat4	projection_matrix(float fov, float aspect_ratio, float near, float far);