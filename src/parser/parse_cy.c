
#include "parser.h"
#include "scene.h"
#include <stdlib.h>
#include <math.h>

static
t_vec3	rotation_from(t_vec3 axis)
{
	float	yaw;
	float	pitch;

	yaw = acosf(vec3_dot(axis, (t_vec3){0, 0, 0}));
	if (axis.x == 0 && axis.z == 0)
		pitch = 0;
	else
		pitch = atan2f(axis.z, axis.x);
	return (t_vec3){pitch, yaw, 0};
}

void	parse_cy(t_scene *scene, t_list *obj_list, const char **str_ref)
{
	t_object	cylinder;
	t_vec3		axis;
	float		diameter;
	float		height;
	t_vec3		color;

	ft_bzero(&cylinder, sizeof(t_object));
	*str_ref += 2;
	cylinder.mesh = &scene->mesh[MESH_CYLINDER];
	skip_space(str_ref);
	cylinder.position = parse_vec3(str_ref);
	skip_space(str_ref);
	axis = parse_vec3(str_ref);
	cylinder.rotation = rotation_from(axis);
	skip_space(str_ref);
	diameter = parse_float(str_ref);
	skip_space(str_ref);
	height = parse_float(str_ref);
	cylinder.scale = (t_vec3){diameter, height, diameter};
	skip_space(str_ref);
	color = parse_vec3(str_ref);
	cylinder.color = vec3_mul(vec3_add(color, (t_vec3){0.5, 0.5, 0.5}), 1.0f / 256);
	line_end(str_ref);
	list_push(obj_list, &cylinder);
}
