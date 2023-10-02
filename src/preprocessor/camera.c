#include "scene.h"
#include "settings.h"

t_mat4	view_matrix(t_vec3 right, t_vec3 up, t_vec3 forward, t_vec3 position);
t_mat4	projection_matrix(float fov, float aspect_ratio, float near, float far);

/*
스크린 공간 -> NDC 공간 변환
: x, y의 범위가 각각 [0, width), [0, height)인 2차원 평면 상의 좌표를
x, y, z의 범위가 모두 [-1, 1]인 3차원 정육면체 공간으로 매핑한다.
*/
static t_vec3	screen_to_ndc_space(t_vec3 screen, float depth, \
										int width, int height)
{
	t_vec3	ndc;

	ndc.x = (screen.x / width) * 2 - 1.0f;
	ndc.y = -(screen.y / height) * 2 + 1.0f;
	ndc.z = depth;
	return (ndc);
}

/*
클립 공간 -> 월드 공간 변환
: 투영 행렬(P) 및 카메라 행렬(V)의 역행렬을 적용하고, 전체 성분을 w로 나눠준다.
(동차좌표계에서 3D좌표로 해석될 수 있도록 w=1로 만들어주어야하기 때문)
*/
static t_vec3	clip_to_world_space(t_vec4 clip, const t_mat4 *pv_inverse)
{
	t_vec4	v4;

	v4 = mat4_mulmv(*pv_inverse, clip);
	vec4_mul(v4, (1 / v4.w));
	return ((t_vec3){v4.x, v4.y, v4.z});
}

/*
그래픽스 파이프라인의 좌표계 매핑 과정
world -> view -> clip -> NDC -> screen
을 반대로 이행함으로써 screen 공간 상의 좌표를 world 공간 기준으로 매핑한다.

<screen 공간 상의 좌표를 world 공간으로 매핑하기>
1. NDC 공간 좌표로 변환 (=[-1,1] 범위로 매핑)
2. clip 공간 좌표로 변환 (=전체 성분에 depth 알맞게 반영)
3. world 공간 좌표로 변환 (=투영 행렬(P) 및 카메라 행렬(V)의 역행렬 적용)

이때, 2차원 평면에서 3차원 공간으로의 매핑이기에 임의의 depth를 설정해야한다.
편의상 near plane 기준 좌표를 구하도록 한다.
(ndc.z = -1, clip.w = NEAR, view.z = NEAR)
*/
static t_vec3	pixel_to_world_space(int pixel_x, int pixel_y, \
										const t_mat4 *pv_inverse)
{
	t_vec3		screen;
	t_vec3		ndc;
	t_vec4		clip;
	t_vec3		world;

	screen = (t_vec3){pixel_x + 0.5, pixel_y + 0.5, 0};
	ndc = screen_to_ndc_space(screen, -1, IMAGE_WIDTH, IMAGE_HEIGHT);
	clip = vec4_mul((t_vec4){ndc.x, ndc.y, ndc.z, 1}, NEAR);
	world = clip_to_world_space(clip, pv_inverse);
	return (world);
}

/*
레이 트레이싱에서 카메라의 파라미터들은 결국 카메라 레이 방향벡터를 구하는데 쓰인다.
매 픽셀마다 PV의 역행렬을 구하는 건 비효율적이므로, 보다 효율적인 동작을 위해
전처리 작업으로서 image plane의 모서리(corner)의 네 점의 world space 기준 좌표를 미리 구해두고
후에 이를 보간하여 사용한다.
*/
int	preprocess_camera(t_camera *cam)
{
	const t_mat4	pv = mat4_mulmm(\
			projection_matrix(cam->fov, (float)IMAGE_WIDTH / IMAGE_HEIGHT, \
																NEAR, FAR), \
			view_matrix(cam->right, cam->up, cam->forward, cam->position));
	const t_mat4	pv_inverse = mat4_inverse(pv);
	const int		corners[4][2] = {{0, 0}, \
									{IMAGE_WIDTH, 0}, \
									{0, IMAGE_HEIGHT}, \
									{IMAGE_WIDTH, IMAGE_HEIGHT}};
	int				i;

	i = 0;
	while (i < 4)
	{
		cam->corners_world_pos[i] = \
			pixel_to_world_space(corners[i][0], corners[i][1], &pv_inverse);
		i++;
	}
	return (0);
}
