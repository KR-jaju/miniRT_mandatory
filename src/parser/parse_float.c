
#include "libft.h"
#include "parser.h"
#include "debug.h"

// 필요시 포맷 체크와 파싱 함수 나눌 것 (25줄 제한)
static bool		_is_valid_float(const char *str_ref);
static float	_parse_float(const char **str_ref);

// DEBUG
float	parse_float(const char **str_ref)
{
	float	f;
	float	exp;

	// 음수인 경우와 시작지점이 '0'인 경우 문제 발생
	if (!('1' <= **str_ref && **str_ref <= '9'))
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	f = 0;
	while (ft_isdigit(**str_ref))
	{
		f *= 10;
		f += **str_ref;
		(*str_ref)++;
	}
	if (**str_ref != '.')
		return (f);
	(*str_ref)++;
	exp = 0.1f;
	while (ft_isdigit(**str_ref))
	{
		f += exp * (**str_ref - '0');
		exp *= 0.1f;
		(*str_ref)++;
	}
	return (f);
}
