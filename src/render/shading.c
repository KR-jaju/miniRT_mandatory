#include "render.h"

// TODO: 폴리곤 메쉬이므로, 필요시 프래그먼트별 계산법 도입할 것 (저해상도 메쉬의 조명 정확도 올리기)
/*
diffuse = 난반사 세기 * 컬러
	난반사 세기: 입사벡터와 노멀벡터의 내적
	컬러: 광원의 색 * 디퓨즈 계수
*/
t_vec3	diffuse_reflection_value(t_material *material, t_vec3 ray_color, \
								t_vec3 incident, t_vec3 normal)
{
	float		brightness;
	t_vec3		color;

	incident = vec3_normalize(incident);
	normal = vec3_normalize(normal);

	brightness = fmaxf(vec3_dot(incident, normal), 0);
	color = vec3_mul(ray_color, material->k_diffuse);
	return (vec3_mul(color, brightness));
}

/*
specular = 하이라이트 세기 * 컬러
	하이라이트 세기: 반사벡터와 시선벡터의 내적 (그리고 광택에 반비례)
	컬러: 광원의 색 * 스페큘러 계수
*/
t_vec3	specular_reflection_value(t_material *material, t_vec3 ray_color, \
								t_vec3 reflection, t_vec3 view)
{
	float		brightness;
	t_vec3		color;

	reflection = vec3_normalize(reflection);
	view = vec3_normalize(view);

	brightness = fmaxf(vec3_dot(reflection, view), 0);
	brightness = powf(brightness, material->shininess);
	color = vec3_mul(ray_color, material->k_specular);
	return (vec3_mul(color, brightness));
}

// TODO: 방향벡터 구하는 함수 작성
t_vec3	incident_direction(void);
t_vec3	reflection_direction(void);
t_vec3	view_direction(void);

/*
교차점 색상 계산:

최종 색상 = 환경광(ambient) + 난반사(diffuse) + 정반사(specular)
(오브젝트의 재질에 따라 난반사와 정반사 항의 비율을 조정한다, 둘을 합하면 1)

ambient: 배경색상 (지역조명 모델이므로 매우 간단)
diffuse: 빛의 입사벡터, 정점 노멀벡터
specular: 빛의 반사벡터, 시선벡터
*/
t_vec3	shade_intersection(t_hit_record *hit, t_scene *scene)
{
	t_vec3		ambient;
	t_vec3		diffuse;
	t_vec3		specular;
	t_material	material;

	ambient = vec3_hadamard(scene->ambient_light, material.color);
	diffuse = diffuse_reflection_value(&material, scene->light.color, \
										incident_direction(), \
										hit->polygon->normal);
	specular = specular_reflection_value(&material, scene->light.color, \
										reflection_direction(), \
										view_direction());
	return (vec3_add(ambient, \
			vec3_add(vec3_mul(diffuse, 1 - material.reflectivity), \
					vec3_mul(specular, material.reflectivity))));
}
/*
사용자 정의 상수값
1. 난반사와 정반사 비율
2. 난반사 계수
3. 정반사 계수
사실적인 묘사를 원하면 physically based rendering 참고
(그래도 멘데이토리에서는 한계 있음)
*/
