#include "parser.h"
#include "scene.h"
#include <stdlib.h>

void parse_a(t_scene *scene, int declared[3], const char **str_ref)
{
	float	intensity;
	t_vec3	color;

	*str_ref += 1;
	if (declared[A] == 1)
		handle_parse_error(ERROR_DUPLIATE_DECLARED);
	else
		declared[A] = 1;
	skip_space(str_ref);
	intensity = parse_float(str_ref);
	skip_space(str_ref);
	color = parse_vec3(str_ref);
	ensure_empty(*str_ref);
	scene->ambient_light = vec3_mul(
			vec3_add(color, vec3(0.5f, 0.5f, 0.5f)),
			intensity / 256.0f);
}

