#include "parser_internal.h"
#include "scene.h"
#include <stdlib.h>

bool	is_normalized(t_vec3 v);

void	parse_c(t_scene *scene, bool declared[3], const char **str_ref)
{
	t_camera*const	camera = &scene->camera;

	*str_ref += 1;
	if (declared[C] == 1)
		handle_parse_error(ERROR_DUPLIATE_DECLARED);
	else
		declared[C] = 1;
	skip_space(str_ref);
	camera->position = parse_vec3(str_ref);
	skip_space(str_ref);
	camera->forward = parse_vec3(str_ref);
	if (!is_normalized(camera->forward))
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	camera->right = vec3_normalize(\
					vec3_cross((t_vec3){0, 1, 0}, camera->forward));
	camera->up = vec3_cross(camera->forward, camera->right);
	skip_space(str_ref);
	camera->fov = parse_float(str_ref);
	if (!(0.0f <= camera->fov && camera->fov <= 180.f))
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	ensure_empty(*str_ref);
}
