#include "libmath.h"
#include "libft.h"
#include <stdlib.h>

t_mat4	mat4_identity(void)
{
	static const float values[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	t_mat4				m;

	ft_memcpy(&m, values, sizeof(m));
	return (m);
}

t_mat4		mat4_by_values(const float values[])
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

t_mat4		mat4_transpose(t_mat4 orig)
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
	float	minor[4] = {
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
/*
// TODO: 형식 맞춰 재작성
t_mat4 mat4_inverse(t_mat4 m) {
    t_mat4 result = mat4_identity();  // 결과 역행렬 초기화
    const int n = 4;
	int row[4];
	int col[4];
	float temp[4];

    // 가우스-조르당 소거법을 사용하여 역행렬 계산
    for (int i = 0; i < n; i++)
	{
        float max = 0.0f;
        for (int j = 0; j < n; j++)
		{
            if (row[j] != 1)
			{
                for (int k = 0; k < n; k++)
				{
                    if (col[k] == 0)
					{
                        float abs_value = fabs(m.e[j][k]);
                        if (abs_value >= max)
						{
                            max = abs_value;
                            row[j] = 1;
                            col[k] = 1;
                        }
                    }
                }
            }
        }

        if (row[i] != 1 || col[i] != 1) {
            // 역행렬을 찾을 수 없는 경우 예외 처리
            return (mat4_identity());
        }

        for (int j = 0; j < n; j++)
		{
            if (j != i)
			{
                temp[j] = m.e[j][i] / m.e[i][i];
                for (int k = 0; k < n; k++)
                    if (k != i)
                        m.e[j][k] -= temp[j] * m.e[i][k];
            }
        }

        for (int j = 0; j < n; j++) {
            if (j != i) {
                m.e[j][i] = -temp[j] / m.e[i][i];
            }
        }

        for (int j = 0; j < n; j++)
		{
            if (j != i)
                for (int k = 0; k < n; k++)
                    if (k != i)
                        m.e[j][k] += m.e[j][i] * m.e[i][k];
        }

        m.e[i][i] = -1.0f / m.e[i][i];
        for (int j = 0; j < n; j++)
            if (j != i)
                m.e[j][i] *= m.e[i][i];
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result.e[i][j] = m.e[i][j];

    return result;
}
*/