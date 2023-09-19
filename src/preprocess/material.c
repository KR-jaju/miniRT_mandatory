#include "scene.h"
#include "settings.h"

t_material	default_material(t_vec3 color)
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
