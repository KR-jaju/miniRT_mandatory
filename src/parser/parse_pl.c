
#include "parser.h"
#include <stdlib.h>
#include <math.h>

static
t_vec3	rotation_from(t_vec3 axis)
{
	float	hypot = sqrtf(axis.x * axis.x + axis.z * axis.z);
	float	yaw;
	float	pitch;

	yaw = acosf(axis.y);
	if (axis.x == 0 && axis.z == 0)
		pitch = 0;
	else
		pitch = atan2f(axis.y, hypot); // radians
	return (t_vec3){pitch, yaw, 0};
}

void	parse_pl(t_scene *scene, t_list *obj_list, const char **str_ref)
{
	t_object	plane;
	t_vec3		normal;
	t_vec3		color;

	ft_bzero(&plane, sizeof(t_object));
	*str_ref += 2;
	plane.mesh = &scene->mesh[MESH_PLANE];
	skip_space(str_ref);
	plane.position = parse_vec3(str_ref);
	skip_space(str_ref);
	normal = parse_vec3(str_ref);
	plane.rotation = rotation_from(normal);
	plane.scale = (t_vec3){1, 1, 1};
	skip_space(str_ref);
	color = parse_vec3(str_ref);
	plane.color = vec3_mul(vec3_add(color, (t_vec3){0.5, 0.5, 0.5}), 1.0f / 256);
	ensure_empty(*str_ref);
	list_push(obj_list, &plane);
}
