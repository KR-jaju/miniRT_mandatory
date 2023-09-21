
#include "parser.h"
#include "scene.h"
#include <stdlib.h>

void	parse_sp(t_scene *scene, t_list *obj_list, const char **str_ref)
{
	t_object	sphere;
	float		radius;
	t_vec3		color;

	ft_bzero(&sphere, sizeof(t_object));
	*str_ref += 2;
	sphere.mesh = &scene->mesh[MESH_SPHERE];
	skip_space(str_ref);
	sphere.position = parse_vec3(str_ref);
	skip_space(str_ref);
	radius = parse_float(str_ref);
	sphere.scale = (t_vec3){radius, radius, radius};
	skip_space(str_ref);
	color = parse_vec3(str_ref);
	sphere.color = vec3_mul(vec3_add(color, (t_vec3){0.5, 0.5, 0.5}), 1.0f / 256);
	ensure_empty(*str_ref);
	list_push(obj_list, &sphere);
}