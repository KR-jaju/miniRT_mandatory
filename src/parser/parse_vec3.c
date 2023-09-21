
#include "parser.h"
#include "libmath.h"
#include <stdlib.h>

// 필요시 포맷 체크와 파싱 함수 나눌 것 (25줄 제한)
static bool		_is_valid_vec3(const char *str_ref);
static t_vec3	_parse_vec3_(const char **str_ref);

// DEBUG
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
