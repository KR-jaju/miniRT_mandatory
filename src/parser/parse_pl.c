#include "parser_internal.h"
#include <stdlib.h>
#include <math.h>

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
		yaw = atan2f(axis.z, axis.x) * 180 / M_PI;
	pitch = acosf(axis.y) * 180 / M_PI;
	return ((t_vec3){pitch, yaw, 0});
}

void	parse_pl(t_scene *scene, t_list *obj_list, const char **str_ref)
{
	t_object	plane;
	t_vec3		normal;
	t_vec3		color;

	ft_bzero(&plane, sizeof(t_object));
	*str_ref += 2;
	plane.mesh = &scene->meshes[MESH_PLANE];
	skip_space(str_ref);
	plane.position = parse_vec3(str_ref);
	skip_space(str_ref);
	normal = parse_vec3(str_ref);
	plane.rotation = rotation_from(normal);
	plane.scale = (t_vec3){1, 1, 1};
	skip_space(str_ref);
	color = parse_vec3(str_ref);
	if (!is_color(color))
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	plane.material.color = rgb_to_vec3(color);
	ensure_empty(*str_ref);
	if (list_push(obj_list, &plane) == -1)
		handle_parse_error(ERROR_MALLOC);
}
