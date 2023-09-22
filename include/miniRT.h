#ifndef MINIRT_H
#define MINIRT_H

# include <stdint.h>
# include "mlx_api.h"
# include "scene.h"
# include "debug.h" // for dev

typedef struct s_program_data
{
	t_mlx	*mlx;
	t_scene	*scene;
	t_image	*img;
}t_program_data;

// init
void	init_scene(t_scene *scene, const char *path);
void	init_mlx(t_mlx *mlx);
void	init_image(t_image *img, void *mlx_conn);

int		render_display(t_program_data *data);
int		keypress_hook(int keycode, void *param);
int		shutdown_program(void *resource);

#endif
