#include "render.h"

// TODO: 차후 포인터와 복사 연산 둘 중 통일 필요
void	translate_matrix(t_vec3 pos, t_mat4 *m);
void	rotate_matrix(t_vec3 rot, t_mat4 *m);
void	scale_matrix(t_vec3 scale, t_mat4 *m);

/*
로컬 공간 -> 월드 공간 매핑

T, R, S 세 개의 행렬을 compose하면 된다.
*/
t_mat4	model_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_mat4	t;
	t_mat4	r;
	t_mat4	s;

	translate_matrix(pos, &t);
	rotate_matrix(rot, &r);
	scale_matrix(scale, &s);
	return (mat4_mulmm(t, mat4_mulmm(r, s)));
}

/*
월드 공간 -> 뷰 공간 매핑

뷰 공간은 카메라의 세 개의 방향벡터가 이루는 공간이므로,
이미 알고있는 카메라 방향벡터를 그대로 열벡터로 삼으면 된다.
세 개의 축이 직교하는 유클리드 공간끼리의 매핑이므로 간단하게 기저벡터의 전환으로 생각할 수 있다.
(right - x축, up - y축, forward - z축)
*/
t_mat4	view_matrix(t_vec3 right, t_vec3 up, t_vec3 forward, t_vec3 pos)
{
	t_mat4	m;

	m.v1 = (t_vec4){right.x, right.y, right.z, 0};
	m.v2 = (t_vec4){up.x, up.y, up.z, 0};
	m.v3 = (t_vec4){forward.x, forward.y, forward.z, 0};
	m.v4 = (t_vec4){pos.x, pos.y, pos.z, 1};
	return (m);
}

t_mat4	projection_matrix(float fov, float aspect_ratio, float near, float far);
