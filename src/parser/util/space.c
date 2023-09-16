
#include "libft.h"
#include "scene.h"

static
int	is_space(char c)
{
	return (c == ' '
		|| c == '\t'
	);
}

void	skip_space(const char **str_ref)
{
	const char	*str = *str_ref;
	int			count;

	count = 0;
	while (str[count] != '\0' && is_space(str[count]))
		count++;
	*str_ref = str + count;
	if (count == 0)
		exit(1);
	return (0);
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
