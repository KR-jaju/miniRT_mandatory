#include "stdlib.h"
#include "scene.h"
#include "parser.h"

static bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	skip_space(const char **str_ref)
{
	while (is_space(**str_ref))
		(*str_ref)++;
}

void	ensure_empty(char const *str)
{
	skip_space(&str);
	if (*str == '\0' || *str == '\n')
		return ;
	handle_parse_error(ERROR_INVALID_LINE_FORMAT);
}
