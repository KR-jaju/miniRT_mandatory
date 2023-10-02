#include "libft.h"
#include "mlx_api.h"
#include "render.h"
#include "settings.h"

/*
카메라 방향벡터: 카메라 좌표->픽셀 좌표

전처리 작업에서 미리 구해둔 image plane의 모서리(corner)의 네 점의 world space 기준 좌표를
선형 보간(linear interpolate)하여 현재 구하고 싶은 픽셀의 world space 기준 좌표를 구하고,
이에 카메라의 좌표를 빼서 카메라 방향벡터를 구한다.
*/
static t_vec3	camera_ray_direction(int x, int y, t_camera *cam, t_image *img)
{
	t_vec3				pixel_world_pos;
	const float			x_percentage = (float)x / img->width;
	const float			y_percentage = (float)y / img->height;
	float				ratio[4];

	ratio[0] = (1.0f - x_percentage) * (1.0f - y_percentage);
	ratio[1] = x_percentage * (1.0f - y_percentage);
	ratio[2] = (1.0f - x_percentage) * y_percentage;
	ratio[3] = x_percentage * y_percentage;
	pixel_world_pos = vec3_interpolate(cam->corners_world_pos, ratio, 4);
	return (vec3_normalize(vec3_sub(pixel_world_pos, cam->position)));
}

/*
교차점 색상 계산:
최종 색상 = 환경광(ambient) + 난반사(diffuse) + 정반사(specular)
	(오브젝트의 재질에 따라 난반사와 정반사 항의 비율을 조정, 둘을 합하면 1)

각 항별 파라미터
- ambient: 배경색상 (지역조명 모델이므로 매우 간단)
- diffuse: 빛의 입사벡터, 교차지점 노말벡터
- specular: 빛의 반사벡터, 시선벡터

교차지점의 노말을 어떻게 설정하냐에 따라 Flat shading과 Smooth shading으로 나뉘어진다.
- 폴리곤의 법선벡터(face normal) 사용 -> Flat shading
- 폴리곤을 이루는 세 점의 정점 노말을 보간(interpolate)하여 얻어낸 노말 사용 -> Smooth shading
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
						view_direction(scene->camera.position, hit->point));
	return (vec3_add(ambient, \
			vec3_add(vec3_mul(diffuse, (float)1 - material->reflectivity), \
					vec3_mul(specular, (float)material->reflectivity))));
}

/*
1. 카메라 레이 생성
2. 오브젝트와 충돌 체크, 가장 가까운 오브젝트 찾음
3.1. 찾은 경우 - 해당 교차지점에 대해 shading하여 반환
3.2. 못 찾은 경우 - 배경 색 반환
*/
t_vec3	render_pixel(int x, int y, t_scene *scene, t_image *img)
{
	t_ray			cam_ray;
	t_hit_record	hit;
	t_hit_record	closest_hit;
	int				i;

	closest_hit.t = INFINITY;
	cam_ray.origin = scene->camera.position;
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
