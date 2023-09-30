#include "libft.h"
#include "libmath.h"
#include "render.h"

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
t_mat4	view_matrix(t_vec3 right, t_vec3 up, t_vec3 forward, t_vec3 position)
{
	t_mat4	r;
	t_mat4	t;

	r.col[0] = (t_vec4){right.x, up.x, forward.x, 0};
	r.col[1] = (t_vec4){right.y, up.y, forward.y, 0};
	r.col[2] = (t_vec4){right.z, up.z, forward.z, 0};
	r.col[3] = (t_vec4){0, 0, 0, 1};
	t = translate_matrix(vec3_mul(position, -1));
	return (mat4_mulmm(r, t));
}

/*
뷰 공간 -> 클립 공간 (NDC공간 아님, 정규화x)

투영 행렬을 구하기 위해 near, far가 필요한 것은 맞는데,
우리는 z버퍼를 사용하지 않으므로 아무값이나 설정해도 무방.
(기본값 0.3, 1000으로 설정할 예정)
*/
t_mat4	projection_matrix(float fov, float aspect_ratio, float near, float far)
{
	const float	fov_radian = M_PI / 180 * fov;
	const float	d = 1.0f / tanf(fov_radian * 0.5f); // n / r, n/r * aspect_ratio
	const float	values[16] = {
		d, 0, 0, 0,
		0, d * aspect_ratio, 0, 0,
		0, 0, -(near + far) / (near - far), 1,
		0, 0, 2 * near * far / (near - far), 0
	};

	return (mat4_by_values(values));
}
