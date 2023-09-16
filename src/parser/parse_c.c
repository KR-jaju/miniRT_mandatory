
#include "parser.h"
#include "scene.h"

static
void	prepare(t_camera *camera)
{
	//t_vec3	up;

	(void)camera;
	//up = camera.
}

int	parse_c(t_scene *scene, int declared[3], const char **str_ref)
{
	int	i;

	if (declared[C])
		return (-1);
	else
		declared[C] = 1;
	skip_space(str_ref);
	scene->camera.eye = parse_vec3(str_ref);
	skip_space(str_ref);
	scene->camera.look_at = parse_vec3(str_ref);
	skip_space(str_ref);
	scene->camera.fov = parse_float(str_ref);
	line_end(str_ref);
	prepare(&scene->camera);
	return (0);
}
