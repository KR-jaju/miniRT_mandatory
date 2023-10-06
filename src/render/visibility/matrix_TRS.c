/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_TRS.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:22 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:23 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libmath.h"

t_mat4	translate_matrix(t_vec3 t)
{
	const float	values[16] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		t.x, t.y, t.z, 1
	};
	t_mat4		m;

	ft_memcpy(&m, values, sizeof(m));
	return (m);
}

// Apply in the order z, x and y (Same as Unity)
t_mat4	rotate_matrix(t_vec3 r)
{
	const float	radian = M_PI / 180;
	const float	values_x[16] = {
		1, 0, 0, 0,
		0, cos(r.x * radian), sin(r.x * radian), 0,
		0, -sin(r.x * radian), cos(r.x * radian), 0,
		0, 0, 0, 1
	};
	const float	values_y[16] = {
		cos(r.y * radian), 0, -sin(r.y * radian), 0,
		0, 1, 0, 0,
		sin(r.y * radian), 0, cos(r.y * radian), 0,
		0, 0, 0, 1
	};
	const float	values_z[16] = {
		cos(r.z * radian), sin(r.z * radian), 0, 0,
		-sin(r.z * radian), cos(r.z * radian), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	return (mat4_mulmm(mat4_by_values(values_y), \
				mat4_mulmm(mat4_by_values(values_x), \
							mat4_by_values(values_z))));
}

t_mat4	scale_matrix(t_vec3 s)
{
	const float	values[16] = {
		s.x, 0, 0, 0,
		0, s.y, 0, 0,
		0, 0, s.z, 0,
		0, 0, 0, 1
	};
	t_mat4		m;

	ft_memcpy(&m, values, sizeof(m));
	return (m);
}
