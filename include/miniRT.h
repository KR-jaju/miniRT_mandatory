#ifndef MINIRT_H
#define MINIRT_H

# include <stdint.h>
# include "mlx_api.h"
# include "scene.h"

# define PROGRAM_NAME 	"miniRT"
# define WINDOW_TITLE 	PROGRAM_NAME

typedef struct s_program_data
{
	t_mlx	*mlx;
	t_scene	*scene;
	t_image	*img;
}t_program_data;

int	render_display(t_program_data *data);
int	shutdown_program(void *resource);
void	init_scene(t_scene *scene, const char *path);

// for dev
int	dummy_scene(t_scene *scene);

#endif
