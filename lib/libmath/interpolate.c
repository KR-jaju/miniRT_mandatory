/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpolate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:47 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:48 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec3	vec3_interpolate(t_vec3 *vectors, float *ratio, int n_vectors)
{
	t_vec3	v;
	int		i;

	v = (t_vec3){0, 0, 0};
	i = 0;
	while (i < n_vectors)
	{
		v = vec3_add(v, vec3_mul(vectors[i], ratio[i]));
		i++;
	}
	return (v);
}
