/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:11 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:12 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

/*
Incident vector: intersection point -> light position
*/
t_vec3	incident_direction(t_vec3 hit_pos, t_vec3 light_pos)
{
	return (vec3_normalize(\
			vec3_sub(light_pos, hit_pos)));
}

/*
Reflection vector: Reflect at the same angle as the incident angle
	R = -i + 2n(i * n)
	i: incident vector, n: normal at intersection
*/
t_vec3	reflection_direction(t_vec3 i, t_vec3 n)
{
	return (vec3_normalize(\
			vec3_add(vec3_mul(i, -1), \
					vec3_mul(vec3_mul(n, vec3_dot(i, n)), 2))));
}

/*
View vector: intersection point -> camera position
*/
t_vec3	view_direction(t_vec3 camera_pos, t_vec3 hit_pos)
{
	return (vec3_normalize(\
			vec3_sub(camera_pos, hit_pos)));
}
