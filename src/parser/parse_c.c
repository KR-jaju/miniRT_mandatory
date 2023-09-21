
#include "parser.h"
#include "scene.h"
#include <stdlib.h>

static
void	prepare(t_camera *camera)
{
	//t_vec3	up;

	(void)camera;
	//up = camera.
}

void	parse_c(t_scene *scene, int declared[3], const char **str_ref)
{
	*str_ref += 1;
	if (declared[C] == 1)
		handle_parse_error(ERROR_DUPLIATE_DECLARED);
	else
		declared[C] = 1;
	skip_space(str_ref);
	scene->camera.position = parse_vec3(str_ref);
	skip_space(str_ref);
	scene->camera.forward = parse_vec3(str_ref);
	skip_space(str_ref);
	scene->camera.fov = parse_float(str_ref);
	ensure_empty(*str_ref);
	prepare(&scene->camera);
}
