
#include "parser.h"
#include "scene.h"
#include <stdlib.h>

void	parse_sp(t_scene *scene, t_list *obj_list, const char **str_ref)
{
	t_object	sphere;
	float		diameter;
	t_vec3		color;

	ft_bzero(&sphere, sizeof(t_object));
	*str_ref += 2;
	sphere.mesh = &scene->meshs[MESH_SPHERE];
	skip_space(str_ref);
	sphere.position = parse_vec3(str_ref);
	skip_space(str_ref);
	diameter = parse_float(str_ref);
	sphere.scale = (t_vec3){diameter, diameter, diameter};
	skip_space(str_ref);
	color = parse_vec3(str_ref);
	sphere.material.color = rgb_to_vec3(color);
	ensure_empty(*str_ref);
	if (list_push(obj_list, &sphere) == -1)
		handle_parse_error(ERROR_MALLOC);
}
