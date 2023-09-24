#include "parser_internal.h"
#include "scene.h"
#include <stdlib.h>


bool	is_color(t_vec3 color);

void	parse_l(t_scene *scene, bool declared[3], const char **str_ref)
{
	float	intensity;
	t_vec3	color;

	*str_ref += 1;
	if (declared[L] == 1)
		handle_parse_error(ERROR_DUPLIATE_DECLARED);
	else
		declared[L] = 1;
	skip_space(str_ref);
	scene->light.position = parse_vec3(str_ref);
	skip_space(str_ref);
	intensity = parse_float(str_ref);
	if (!(0.0f <= intensity && intensity <= 1.0f))
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	skip_space(str_ref);
	color = parse_vec3(str_ref);
	if (!is_color(color))
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	scene->light.color = rgb_to_vec3(vec3_mul(color, intensity));
	ensure_empty(*str_ref);
}
