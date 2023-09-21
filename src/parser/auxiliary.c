
#include "stdlib.h"
#include "scene.h"

static
bool	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

void	skip_space(const char **str_ref)
{
	while (is_space(**str_ref))
		(*str_ref)++;
}

void	line_end(const char **str_ref)
{
	const char	*str = *str_ref;

	while (str[0] != '\0' && str[0] != '\n' && is_space(str[0]))
		str++;
	if (str[0] == '\0' || str[0] == '\n')
		return ;
	exit(1);
}
