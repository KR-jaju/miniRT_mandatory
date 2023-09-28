#include "parser_internal.h"

void	skip_space(const char **str_ref)
{
	while (**str_ref == ' ' || **str_ref == '\t')
		(*str_ref)++;
}

void	ensure_empty(const char *str)
{
	skip_space(&str);
	if (*str == '\0' || *str == '\n')
		return ;
	handle_parse_error(ERROR_INVALID_LINE_FORMAT);
}

t_vec3	rgb_to_vec3(t_vec3 color)
{
	return (vec3_mul(vec3_add(color, (t_vec3){0.5, 0.5, 0.5}), 1.0f / 256));
}

bool	is_color(t_vec3 color)
{
	if ((float)color.x - (int)color.x > 0
		|| (float)color.y - (int)color.y > 0
		|| (float)color.z - (int)color.z > 0)
		return (false);
	return (0 <= color.x && color.x <= 255
		&& 0 <= color.y && color.y <= 255
		&& 0 <= color.z && color.z <= 255);
}

bool	is_normalized(t_vec3 v)
{
	const float	deviation = vec3_length(v) - 1;

	return (-EPSILON <= deviation && deviation <= EPSILON);
}
