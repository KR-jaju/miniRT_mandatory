#include "parser_internal.h"
#include "scene.h"
#include <stdlib.h>
#include <math.h>

// TODO: 라디안 단위인지 육십분법 단위인지 확인 필요 (육십분법이어야함)
static
t_vec3	rotation_from(t_vec3 axis)
{
	const float	hypot = sqrtf(axis.x * axis.x + axis.z * axis.z);
	float		yaw;
	float		pitch;

	yaw = acosf(axis.y) * 180 / M_PI;
	if (axis.x == 0 && axis.z == 0)
		pitch = 0;
	else
		pitch = atan2f(axis.y, hypot) * 180 / M_PI;
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
	cylinder.material.color = rgb_to_vec3(color);
	ensure_empty(*str_ref);
	if (list_push(obj_list, &cylinder) == -1)
		handle_parse_error(ERROR_MALLOC);
}
