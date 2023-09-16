
#include "parser.h"
#include "scene.h"

int	parse_l(t_scene *scene, int declared[3], const char **str_ref)
{
	float	intensity;
	t_vec3	color;

	if (declared[L])
		return (-1);
	else
		declared[L] = 1;
	skip_space(str_ref);
	intensity = parse_float(str_ref);
	skip_space(str_ref);
	color = parse_vec3(str_ref);
	line_end(str_ref);
	scene->ambient_light = vec3_mul(
			vec3_add(color, vec3(0.5f, 0.5f, 0.5f)),
			intensity / 256.0f);
	return (0);
}
