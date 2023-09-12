#include "libft.h"
#include "mlx.h"
#include "miniRT.h"
#include "render.h"
#include "mlx_api.h"

// TODO: 차후 최적화를 위해 함수 호출 최소화
/*
카메라 방향벡터: 픽셀 좌표-카메라 좌표
이후 모든 계산은 월드 공간 기준으로 이루어질 것이므로 카메라 방향벡터 또한 월드좌표계 기준으로 구한다.

world space상에서의 픽셀 좌표 구하기
1. NDC 좌표로 변환 (=[-1,1] 범위로 매핑)
2. 투영 행렬(P) 및 카메라 행렬(V)의 역행렬 적용하기
3. w 성분을 1로 만들어주기 위해 전체 성분 w값으로 나누기
	(선형변환의 성질에 의해 이 나눗셈 연산을 이때 해도 상관없음)
*/
static t_vec3	camera_ray_direction(int x, int y, t_camera *cam, t_image *img)
{
	t_vec3	ndc_pos;
	t_vec4	world_pos;

	ndc_pos.x = ((x + 0.5) / img->width) * 2 - 1;
	ndc_pos.y = 1 - ((y + 0.5) / img->height) * 2;
	ndc_pos.z = 0; // -1~1 사이면 아무 값이나 상관없음

	world_pos = mat4_mulmv(\
			(mat4_inverse(mat4_mulmm(\
				projection_matrix(cam->fov, img->aspect_ratio, NEAR, FAR), \
				view_matrix(cam->eye, cam->look_at, cam->up)))), \
			vec4(ndc_pos.x, ndc_pos.y, ndc_pos.z, 1));
	world_pos = vec4_mul(world_pos, (1 / world_pos.w));

	return (vec3_normalize(vec3(world_pos.x - cam->eye.x, \
								world_pos.y - cam->eye.y, \
								world_pos.z - cam->eye.z)));
}

/*
1. 카메라 레이 생성
2. 오브젝트와 충돌 체크, 가장 가까운 오브젝트 찾음
3.1. 찾은 경우 -
		오브젝트-light 레이 생성
		다른 오브젝트가 가리고 있는 경우 반영x
		다른 오브젝트가 가리지 않고 있는 경우 반영o
3.2. 못 찾은 경우 - 배경 색 반환
*/
t_vec3	compute_pixel_color(int x, int y, t_scene *scene, t_image *img)
{
	t_ray			cam_ray;
	t_object		*object;
	t_hit_record	hit;
	t_hit_record	closest_hit;

	closest_hit.t = INFINITY;
	cam_ray.origin = scene->camera.eye;
	cam_ray.dir = camera_ray_direction(x, y, &scene->camera, img);
	object = &scene->objects[0];
	while (object)
	{
		if (ray_object_intersection(&cam_ray, object, &hit) == true \
			&& hit.t < closest_hit.t)
			ft_memcpy(&closest_hit, &hit, sizeof(t_hit_record));
		object++;
	}
	if (closest_hit.t == INFINITY)
		return (scene->ambient_light);
	else
		return (shade_intersection(&closest_hit, scene));
}

/*
1. 현재 처리해야하는 픽셀 컬러 계산
2. 계산된 픽셀 이미지에 반영
3. 이미지를 윈도우에 put
*/
int	render_to_window(t_program_data *data)
{
	t_mlx	*mlx;
	t_scene	*scene;
	t_image	*img;
	t_pixel	p;

	mlx = data->mlx;
	scene = data->scene;
	img = data->img;
	if (img->progress == img->n_pixels)
		return (0);
	p.y = (img->progress + 1) / img->width;
	p.x = img->progress - (p.y * img->height);
	p.color = compute_pixel_color(p.x, p.y, scene, img);
	put_pixel_to_image(p, img);
	mlx_put_image_to_window(mlx->conn, mlx->win, img->addr, 0, 0);
	img->progress++;
	return (0);
}
