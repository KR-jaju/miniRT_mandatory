#include "libft.h"
#include "mlx.h"
#include "miniRT.h"
#include "render.h"
#include "mlx_api.h"

t_mat4	projection_matrix(void);
t_mat4	view_matrix(void);

// TODO: 차후 최적화를 위해 함수 호출 최소화
/*
카메라 방향벡터: 픽셀 좌표-카메라 좌표

world space상에서의 픽셀 좌표 구하기
1. NDC 좌표로 변환
2. 투영 행렬(P)의 역행렬 적용하기
2. 카메라 행렬(V)의 역행렬 적용하기
*/
t_vec3	camera_ray_direction(int x, int y, t_camera *cam, t_image *img)
{
	t_vec3	ndc_pos;
	t_vec4	world_pos;

	ndc_pos.x = ((x + 0.5) / img->width) * 2 - 1;
	ndc_pos.y = 1 - ((y + 0.5) / img->height) * 2;
	ndc_pos.z = 0; // -1~1 사이면 아무 값이나 상관없음

	world_pos = mat4_mulmv(\
			(mat4_inverse(mat4_mulmm(projection_matrix(), view_matrix()))), \
			vec4(ndc_pos.x, ndc_pos.y, ndc_pos.z, 1));
	world_pos = vec4_mul(world_pos, (1 / world_pos.z));

	return (vec3_normalize(vec3(world_pos.x - cam->position.x, \
								world_pos.y - cam->position.y, \
								world_pos.z - cam->position.z)));
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
t_vec3	calculate_pixel_color(int x, int y, t_scene *scene, t_image *img)
{
	t_ray			cam_ray;
	t_object		*object;
	t_hit_record	hit;
	t_hit_record	closest_hit;

	cam_ray.origin = scene->camera.position;
	cam_ray.dir = camera_ray_direction(x, y, &scene->camera, img); // 카메라 레이 계산
	object = &scene->objects[0];
	closest_hit.t = INFINITY;
	while (object)
	{
		if (intersection_check(object, cam_ray, &hit) \
			&& hit.t < closest_hit.t)
			ft_memcpy(&closest_hit, &hit, sizeof(t_hit_record));
		object++;
	}
	if (closest_hit.t == INFINITY)
		return (scene->ambient_light);
	else
		return (calculate_intersection_color(closest_hit.object, scene));
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
	p.color = calculate_pixel_color(p.x, p.y, scene, img);
	put_pixel_to_image(p, img);
	mlx_put_image_to_window(mlx->conn, mlx->win, img->addr, 0, 0);
	img->progress++;
	return (0);
}
