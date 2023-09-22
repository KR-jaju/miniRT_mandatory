#include "scene.h"
#include "settings.h"
#include "render.h"
#include "debug.h"

static t_vec3	ndc_to_world_space(t_vec3 ndc, const t_mat4 *pv_inverse)
{
	t_vec4	v4;

	v4 = mat4_mulmv(*pv_inverse, (t_vec4){ndc.x, ndc.y, ndc.z, 1});
	vec4_mul(v4, (1 / v4.w));
	return ((t_vec3){v4.x, v4.y, v4.z});
}

static t_vec3	screen_to_ndc(int screen_x, int screen_y, int width, int height)
{
	t_vec3	ndc;

	ndc.x = ((screen_x + 0.5) / width) * 2 - 1;
	ndc.y = 1 - ((screen_y + 0.5) / height) * 2;
	ndc.z = 0; // -1~1 사이면 아무 값이나 상관없음
	return (ndc);
}

/*
world space상에서의 픽셀 좌표 구하기
1. NDC 좌표로 변환 (=[-1,1] 범위로 매핑)
2. 투영 행렬(P) 및 카메라 행렬(V)의 역행렬 적용하기
3. w 성분을 1로 만들어주기 위해 전체 성분 w값으로 나누기
	(선형변환의 성질에 의해 이 나눗셈 연산을 이때 해도 상관없음)

구해야하는 이미지 플레인 모서리 좌표
(0, 0), (WIDTH, 0), (0, HEIGHT), (WIDTH, HEIGHT)
*/
void camera_fill_corners_world_pos(t_camera *cam)
{
	const t_mat4	pv = mat4_mulmm(\
			projection_matrix(cam->fov, \
							(float)IMAGE_WIDTH / IMAGE_HEIGHT, NEAR, FAR), \
			view_matrix(cam->right, cam->up, cam->forward, cam->position));
	const t_mat4	pv_inverse = mat4_inverse(pv);
	int				corners[4][2] = {{0, 0}, \
									{IMAGE_WIDTH, 0}, \
									{0, IMAGE_HEIGHT}, \
									{IMAGE_WIDTH, IMAGE_HEIGHT}};
	t_vec3			ndc;
	int				i;

	i = 0;
	while (i < 4)
	{
		ndc = screen_to_ndc(corners[i][0], corners[i][1], \
							IMAGE_WIDTH, IMAGE_HEIGHT);
		cam->corners_world_pos[i] = ndc_to_world_space(ndc, &pv_inverse);
		// printf("%dth corner: ", i);
		// print_vec3(cam->corners_world_pos[i]);
		i++;
	}
}
