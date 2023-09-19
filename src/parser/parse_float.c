
#include "libft.h"

float	parse_float(const char **str_ref)
{
	float	f;
	float	exp;

	if (!('1' <= **str_ref && **str_ref <= '9'))
		exit(1);
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
