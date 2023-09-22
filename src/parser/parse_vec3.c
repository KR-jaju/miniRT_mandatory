
#include "parser.h"
#include "libmath.h"
#include <stdlib.h>

t_vec3	parse_vec3(const char **str_ref)
{
	t_vec3	v;

	v.x = parse_float(str_ref);
	if (*(*str_ref)++ != ',')
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	v.y = parse_float(str_ref);
	if (*(*str_ref)++ != ',')
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	v.z = parse_float(str_ref);
	return (v);
}
