
#include "parser.h"
#include "libmath.h"
#include <stdlib.h>

t_vec3	parse_vec3(const char **str_ref)
{
	t_vec3	v;

	v.x = parse_float(str_ref);
	if (*(*str_ref)++ != ',')
		exit(1);
	v.y = parse_float(str_ref);
	if (*(*str_ref)++ != ',')
		exit(1);
	v.z = parse_float(str_ref);
	return (v);
}
