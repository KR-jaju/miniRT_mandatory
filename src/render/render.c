#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "miniRT.h"
#include "render.h"
#include "mlx_api.h"
#include "console.h"
#include "settings.h"

/*
카메라 방향벡터: 픽셀 좌표-카메라 좌표
이후 모든 계산은 월드 공간 기준으로 이루어질 것이므로 카메라 방향벡터 또한 월드좌표계 기준으로 구한다.

world space상에서의 픽셀 좌표 구하기
1. NDC 좌표로 변환 (=[-1,1] 범위로 매핑)
2. 투영 행렬(P) 및 카메라 행렬(V)의 역행렬 적용하기
3. w 성분을 1로 만들어주기 위해 전체 성분 w값으로 나누기
	(선형변환의 성질에 의해 이 나눗셈 연산을 이때 해도 상관없음)
*/
// TODO: 전처리 과정에서 저장된 행렬 통해 구하도록 수정
static t_vec3	camera_ray_direction(int x, int y, t_camera *cam, t_image *img)
{
	t_vec3	ndc_pos;
	// t_vec4	world_pos;

	(void) cam;
	ndc_pos.x = ((x + 0.5) / img->width) * 2 - 1;
	ndc_pos.y = 1 - ((y + 0.5) / img->height) * 2;
	ndc_pos.z = 0; // -1~1 사이면 아무 값이나 상관없음

	// world_pos = mat4_mulmv(\
	// 		(mat4_transpose(mat4_mulmm(\
	// 			projection_matrix(cam->fov, img->aspect_ratio, NEAR, FAR), \
	// 			view_matrix(cam->eye, cam->look_at, cam->up)))), \
	// 		vec4(ndc_pos.x, ndc_pos.y, ndc_pos.z, 1)); // TRANSPOSE X -> INVERSE
	// world_pos = vec4_mul(world_pos, (1 / world_pos.w));

	// return (vec3_normalize(vec3(world_pos.x - cam->eye.x, \
	// 							world_pos.y - cam->eye.y, \
	// 							world_pos.z - cam->eye.z)));
	return (vec3_normalize(vec3(ndc_pos.x, ndc_pos.y, 1)));
}

/*
교차점 색상 계산:

최종 색상 = 환경광(ambient) + 난반사(diffuse) + 정반사(specular)
(오브젝트의 재질에 따라 난반사와 정반사 항의 비율을 조정한다, 둘을 합하면 1)

ambient: 배경색상 (지역조명 모델이므로 매우 간단)
diffuse: 빛의 입사벡터, 정점 노멀벡터
specular: 빛의 반사벡터, 시선벡터
*/
static t_vec3	shading(t_hit_record *hit, const t_scene *scene)
{
	const t_material	*material = hit->material;
	const t_vec3		incident = incident_direction(\
									hit->point, scene->light.position);
	t_vec3				ambient;
	t_vec3				diffuse;
	t_vec3				specular;

	if (SMOOTH_SHADING == 1)
		hit->normal = interpolate_normal(hit->point, hit->triangle);
	else
		hit->normal = hit->triangle->face_normal;
	ambient = vec3_hadamard(scene->ambient_light, material->color);
	diffuse = diffuse_reflection_value(material, scene->light.color, \
										incident, hit->normal);
	specular = specular_reflection_value(material, scene->light.color, \
						reflection_direction(incident, hit->normal), \
						view_direction(scene->camera.eye, hit->point));

	return (vec3_add(ambient, \
			vec3_add(vec3_mul(diffuse, (float)1 - material->reflectivity), \
					vec3_mul(specular, (float)material->reflectivity))));
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
t_vec3	render_pixel(int x, int y, t_scene *scene, t_image *img)
{
	t_ray			cam_ray;
	t_hit_record	hit;
	t_hit_record	closest_hit;
	int				i;

	closest_hit.t = INFINITY;
	cam_ray.origin = scene->camera.eye;
	cam_ray.dir = camera_ray_direction(x, y, &scene->camera, img);
	i = 0;
	while (i < scene->n_objects)
	{
		if (ray_object_intersection(&cam_ray, &scene->objects[i], &hit) == true \
			&& hit.t < closest_hit.t)
			ft_memcpy(&closest_hit, &hit, sizeof(t_hit_record));
		i++;
	}
	if (closest_hit.t == INFINITY)
		return (scene->ambient_light);
	else
		return (shading(&closest_hit, scene));
}

//TODO: 진척도에 따라 메세지 출력
/*
1. 현재 처리해야하는 픽셀 컬러 계산
2. 계산된 픽셀 이미지에 반영
3. 이미지를 윈도우에 put
*/
void	render_image(int progress, t_scene *scene, t_image *img, bool *done)
{
	t_pixel	p;

	p.y = progress / img->width;
	p.x = progress - (p.y * img->width);
	p.color = render_pixel(p.x, p.y, scene, img);
	put_pixel_to_image(p, img);
	if (progress == img->n_pixels)
		*done = true;
}

int	render_display(t_program_data *data)
{
	static bool	done = false;
	static int	progress = 0;

	if (done)
		return (0);
	if (progress == 0)
		console_msg(MSG_RENDER_START"\n"MSG_RENDER_PROGRESS);
	render_image(progress, data->scene, data->img, &done);
	if (progress % 5000 == 0 || done)
	{
		mlx_put_image_to_window(data->mlx->conn,
								data->mlx->win, data->img->addr, 0, 0);
		printf("progress: %d / %d\n", progress, data->img->n_pixels);
	}
	progress++;
	if (done)
		console_msg(MSG_RENDER_DONE);
	return (0);
}
