/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:06:03 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:06:04 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

float	vec4_length(t_vec4 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w));
}

t_vec4	vec4_normalize(t_vec4 v)
{
	const float	length = sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);

	return (vec4(v.x / length, v.y / length, v.z / length, v.w / length));
}
