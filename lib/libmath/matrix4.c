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

/*
col/row
01 * 12 * 23 + 02 * 13 * 21 + 03 * 11 * 22
-
03 * 12 * 21 + 01 * 13 * 22 + 02 * 11 * 23
*/
float	mat4_determinant(t_mat4	m)
{
	const float	minor[4] = {
		m.e[1][1] * (m.e[2][2] * m.e[3][3] - m.e[3][2] * m.e[2][3])
		- m.e[2][1] * (m.e[1][2] * m.e[3][3] - m.e[3][2] * m.e[1][3])
		+ m.e[3][1] * (m.e[1][2] * m.e[2][3] - m.e[2][2] * m.e[1][3]),
		m.e[0][1] * (m.e[2][2] * m.e[3][3] - m.e[3][2] * m.e[2][3])
		- m.e[2][1] * (m.e[0][2] * m.e[3][3] - m.e[3][2] * m.e[0][3])
		+ m.e[3][1] * (m.e[0][2] * m.e[2][3] - m.e[2][2] * m.e[0][3]),
		m.e[0][1] * (m.e[1][2] * m.e[3][3] - m.e[3][2] * m.e[1][3])
		- m.e[1][1] * (m.e[0][2] * m.e[3][3] - m.e[3][2] * m.e[0][3])
		+ m.e[3][1] * (m.e[0][2] * m.e[1][3] - m.e[1][2] * m.e[0][3]),
		m.e[0][1] * (m.e[1][2] * m.e[2][3] - m.e[2][2] * m.e[1][3])
		- m.e[1][1] * (m.e[0][2] * m.e[2][3] - m.e[2][2] * m.e[0][3])
		+ m.e[2][1] * (m.e[0][2] * m.e[1][3] - m.e[1][2] * m.e[0][3])
	};

	return (m.e[0][0] * minor[0] - m.e[1][0] * minor[1]
		+ m.e[2][0] * minor[2] - m.e[3][0] * minor[3]);
}

float	mat4_cofactor(t_mat4 m, int row, int column)
{
	t_mat4	tmp;
	int		i;

	tmp = m;
	i = 0;
	while (i < 4)
	{
		tmp.e[column][i] = (i == row);
		i++;
	}
	if ((row + column) % 2 == 0)
		return (mat4_determinant(tmp));
	return (-mat4_determinant(tmp));
}

t_mat4	mat4_inverse(t_mat4 m)
{
	float const	det = mat4_determinant(m);
	t_mat4		inverse;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			inverse.e[i][j] = mat4_cofactor(m, i, j) / det;
			j++;
		}
		i++;
	}
	return (inverse);
}
