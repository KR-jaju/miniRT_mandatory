#include "mlx.h"
#include "miniRT.h"
#include "render.h"
#include "mlx_api.h"

/*
1. 카메라 레이 생성
2. 오브젝트와 충돌 체크, 가장 가까운 오브젝트 찾음
3.1. 찾은 경우 -
		오브젝트-light 레이 생성
		다른 오브젝트가 가리고 있는 경우 반영x
		다른 오브젝트가 가리지 않고 있는 경우 반영o
3.2. 못 찾은 경우 - 배경 색 반환
*/
t_vec3	calculate_pixel_color(int x, int y, t_scene *scene)
{
	t_ray			cam_ray;
	t_object		*object;
	t_hit_record	closest_hit;

	cam_ray.origin = scene->camera.position;
	cam_ray.dir = get_camera_ray(&scene->camera); // 카메라 레이 계산
	object = &scene->objects[0];
	closest_hit.t = INFINITY;
	while (object)
	{
		if (intersection_check(object, cam_ray, &closest_hit.t))
			closest_hit.object = object;
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
	p.color = calculate_pixel_color(p.x, p.y, scene);
	put_pixel_to_image(img, p);
	mlx_put_image_to_window(mlx->conn, mlx->win, img->addr, 0, 0);
	img->progress++;
	return (0);
}
