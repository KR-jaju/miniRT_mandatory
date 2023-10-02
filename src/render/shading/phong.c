#include "render.h"

/*
diffuse = diffuse intensity * color
- diffuse intensity: Dot product of incident and intersection normal
- color: Color of light * Diffuse coefficient
*/
t_vec3	diffuse_reflection_value(const t_material *material, \
										t_vec3 ray_color, \
										t_vec3 incident, t_vec3 normal)
{
	float		intensity;
	t_vec3		color;

	intensity = fmaxf(vec3_dot(incident, normal), 0);
	color = vec3_mul(ray_color, material->k_diffuse);
	return (vec3_mul(color, intensity));
}

/*
specular = highlight intensity * Color
- highlight intensity: Dot product of reflection and view vector
reflection vector and gaze vector dot product
(and inversely proportional to gloss)
- Color: Color of light source * Spectacular coefficient
*/
t_vec3	specular_reflection_value(const t_material *material, \
										t_vec3 ray_color, \
										t_vec3 reflection, t_vec3 view)
{
	float		intensity;
	t_vec3		color;

	intensity = fmaxf(vec3_dot(reflection, view), 0);
	intensity = powf(intensity, material->shininess);
	color = vec3_mul(ray_color, material->k_specular);
	return (vec3_mul(color, intensity));
}
