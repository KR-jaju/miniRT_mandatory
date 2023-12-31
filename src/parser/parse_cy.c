/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:45 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:46 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "scene.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

bool	is_color(t_vec3 color);
bool	is_normalized(t_vec3 v);

static
t_vec3	rotation_from(t_vec3 axis)
{
	const float	hypot = sqrtf(axis.x * axis.x + axis.z * axis.z);
	float		yaw;
	float		pitch;

	if (!is_normalized(axis))
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	if (hypot == 0)
		yaw = 0;
	else
		yaw = atan2f(axis.x, axis.z) * 180 / M_PI;
	pitch = acosf(axis.y) * 180 / M_PI;
	return ((t_vec3){pitch, yaw, 0});
}

void	parse_cy(t_scene *scene, t_list *obj_list, const char **str_ref)
{
	t_object	cylinder;
	float		diameter;
	float		height;
	t_vec3		color;

	ft_bzero(&cylinder, sizeof(t_object));
	*str_ref += 2;
	cylinder.mesh = &scene->meshes[MESH_CYLINDER];
	skip_space(str_ref);
	cylinder.position = parse_vec3(str_ref);
	skip_space(str_ref);
	cylinder.rotation = rotation_from(parse_vec3(str_ref));
	skip_space(str_ref);
	diameter = parse_float(str_ref);
	skip_space(str_ref);
	height = parse_float(str_ref);
	cylinder.scale = (t_vec3){diameter, height, diameter};
	skip_space(str_ref);
	color = parse_vec3(str_ref);
	if (!is_color(color))
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	cylinder.material.color = rgb_to_vec3(color);
	ensure_empty(*str_ref);
	if (list_push(obj_list, &cylinder) == -1)
		handle_parse_error(ERROR_MALLOC);
}
