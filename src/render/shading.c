#include "render.h"

static t_material	default_material(t_vec3 color)
{
	static t_material	material = {\
									(t_vec3){0, 0, 0}, \
									REFLECTIVITY, \
									K_DIFFUSE, \
									K_SPECULAR, \
									SHININESS, \
									};

	material.color = color;
	return (material);
}

/*
diffuse = 난반사 세기 * 컬러
	- 난반사 세기: 입사벡터와 노멀벡터의 내적
	- 컬러: 광원의 색 * 디퓨즈 계수
*/
static t_vec3	diffuse_reflection_value(const t_material *material, \
										t_vec3 ray_color, \
										t_vec3 incident, t_vec3 normal)
{
	float		brightness;
	t_vec3		color;

	brightness = fmaxf(vec3_dot(incident, normal), 0);
	color = vec3_mul(ray_color, material->k_diffuse);
	return (vec3_mul(color, brightness));
}

/*
specular = 하이라이트 세기 * 컬러
	- 하이라이트 세기: 반사벡터와 시선벡터의 내적 (그리고 광택에 반비례)
	- 컬러: 광원의 색 * 스페큘러 계수
*/
static t_vec3	specular_reflection_value(const t_material *material, \
										t_vec3 ray_color, \
										t_vec3 reflection, t_vec3 view)
{
	float		brightness;
	t_vec3		color;

	brightness = fmaxf(vec3_dot(reflection, view), 0);
	brightness = powf(brightness, material->shininess);
	color = vec3_mul(ray_color, material->k_specular);
	return (vec3_mul(color, brightness));
}

static void	barycentric_coordinates(t_vec3 p, t_vec3 *abc, float *barycentric)
{
	const float area_abc = vec3_length(\
				vec3_cross(vec3_sub(abc[B], abc[A]), vec3_sub(abc[C], abc[A])));
	const float area_abp = vec3_length(\
				vec3_cross(vec3_sub(abc[B], abc[A]), vec3_sub(p, abc[A])));
	const float area_acp = vec3_length(\
				vec3_cross(vec3_sub(abc[A], abc[C]), vec3_sub(p, abc[C])));
	const float area_bcp = vec3_length(\
				vec3_cross(vec3_sub(abc[C], abc[B]), vec3_sub(p, abc[B])));
	
	barycentric[A] = area_bcp / area_abc;
	barycentric[B] = area_acp / area_abc;
	barycentric[C] = area_abp / area_abc;
}

t_vec3	interpolate_normal(t_vec3 p, t_triangle *t)
{
	float	ratio[3];
	t_vec3	normal[3];

	barycentric_coordinates(p, t->vertices, ratio);
	normal[A] = vec3_mul(t->vertex_normals[A], ratio[A]);
	normal[B] = vec3_mul(t->vertex_normals[B], ratio[B]);
	normal[C] = vec3_mul(t->vertex_normals[C], ratio[C]);
	return (vec3_normalize(\
					vec3_add(vec3_add(normal[A], normal[B]), normal[C])));
}

/*
교차점 색상 계산:

최종 색상 = 환경광(ambient) + 난반사(diffuse) + 정반사(specular)
(오브젝트의 재질에 따라 난반사와 정반사 항의 비율을 조정한다, 둘을 합하면 1)

ambient: 배경색상 (지역조명 모델이므로 매우 간단)
diffuse: 빛의 입사벡터, 정점 노멀벡터
specular: 빛의 반사벡터, 시선벡터
*/
t_vec3	shade_intersection(t_hit_record *hit, const t_scene *scene)
{
	const t_material	material = default_material(hit->color);
	const t_vec3		incident = incident_direction(\
									hit->point, scene->light.position);
	t_vec3				ambient;
	t_vec3				diffuse;
	t_vec3				specular;

	hit->normal = interpolate_normal(hit->point, hit->triangle);
	ambient = vec3_hadamard(scene->ambient_light, material.color);
	diffuse = diffuse_reflection_value(&material, scene->light.color, \
										incident, hit->normal);
	specular = specular_reflection_value(&material, scene->light.color, \
						reflection_direction(incident, hit->normal), \
						view_direction(scene->camera.eye, hit->point));
	
	return (vec3_add(ambient, \
			vec3_add(vec3_mul(diffuse, (float)1 - material.reflectivity), \
					vec3_mul(specular, (float)material.reflectivity))));
}
/*
사용자 정의 상수값
1. 난반사와 정반사 비율
2. 난반사 계수
3. 정반사 계수
사실적인 묘사를 원하면 physically based rendering 참고
(그래도 멘데이토리에서는 한계 있음)
*/
