#ifndef MINIRT_H
#define MINIRT_H

# include <stdint.h>
# include "mlx_api.h"
# include "scene.h"

typedef struct s_program_data
{
	t_mlx	*mlx;
	t_scene	*scene;
	t_image	*img;
}t_program_data;

int	render_to_window(t_program_data *data);
int	shutdown_program(void *resource);
int	parse_scene(t_scene *scene, const char *path);

// for dev
int	dummy_scene(t_scene *scene);

#endif
