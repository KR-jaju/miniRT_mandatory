/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:03:51 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:03:52 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "debug.h"

void	print_vec3(t_vec3 v)
{
	printf("x:%f y:%f z:%f\n", v.x, v.y, v.z);
}

void	print_vec4(t_vec4 v)
{
	printf("x:%f y:%f z:%f w:%f\n", v.x, v.y, v.z, v.w);
}

void	print_mat4(t_mat4 m)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%f ", m.e[j][i]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("------------------\n");
}

int	radian_to_degree(float r)
{
	return (r / M_PI * 180);
}
