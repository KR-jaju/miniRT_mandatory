#include "render.h"

/*
diffuse = 난반사 세기 * 컬러
	- 난반사 세기: 입사벡터와 노멀벡터의 내적
	- 컬러: 광원의 색 * 디퓨즈 계수
*/
t_vec3	diffuse_reflection_value(const t_material *material, \
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
t_vec3	specular_reflection_value(const t_material *material, \
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
