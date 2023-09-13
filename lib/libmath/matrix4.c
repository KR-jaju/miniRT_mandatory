#include "libmath.h"
#include "libft.h"

t_mat4	identity_mat4(void)
{
	static const t_mat4 m = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

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
			m.e[j][i] = vec4_dot(b.col[i], \
					(t_vec4){a.e[0][j], a.e[1][j], a.e[2][j], a.e[3][j]});
			j++;
		}
		i++;
	}
	return (m);
}
