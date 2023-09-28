#include "libmath.h"
#include "libft.h"
#include <stdlib.h>

t_mat4	mat4_identity(void)
{
	static const float	values[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	t_mat4				m;

	ft_memcpy(&m, values, sizeof(m));
	return (m);
}

t_mat4	mat4_by_values(const float values[])
{
	t_mat4	m;

	ft_memcpy(&m, values, sizeof(m));
	return (m);
}

t_mat4	mat4_mulmm(t_mat4 a, t_mat4 b)
{
	t_mat4	m;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.e[i][j] = vec4_dot(b.col[i], \
					(t_vec4){a.e[0][j], a.e[1][j], a.e[2][j], a.e[3][j]});
			j++;
		}
		i++;
	}
	return (m);
}

t_mat4	mat4_transpose(t_mat4 orig)
{
	t_mat4	m;
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			m.e[j][i] = orig.e[i][j];
			j++;
		}
		i++;
	}
	return (m);
}
