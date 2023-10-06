/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:55 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:56 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec3	vec3(float x, float y, float z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	return (vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	return (vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vec3	vec3_mul(t_vec3 v, float a)
{
	return (vec3(v.x * a, v.y * a, v.z * a));
}

float	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}
