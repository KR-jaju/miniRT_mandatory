
#include "parser_internal.h"
#include "scene.h"
#include <stdlib.h>

// TODO: 파싱한 forward 벡터가 normalized 벡터 아닐시 예외 처리
// TODO: 파싱값 Range 체크
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
	camera->right = vec3_normalize(\
					vec3_cross((t_vec3){0, 1, 0}, camera->forward));
	camera->up = vec3_cross(camera->forward, camera->right);
	skip_space(str_ref);
	camera->fov = parse_float(str_ref);
	ensure_empty(*str_ref);
}
