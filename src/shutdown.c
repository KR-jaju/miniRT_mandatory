#include <stdlib.h>
#include "miniRT.h"
#include "mlx_api.h"
#include "mesh.h"
#include "console.h"

static void	destroy_scene(t_scene *scene)
{
	t_object	*obj;
	int			i;

	i = 0;
	while (i < scene->n_objects)
	{
		obj = &scene->objects[i];
		free(obj->vertices);
		free(obj->vertex_normals);
		free(obj->triangles);
		i++;
	}
}

int	shutdown_program(t_program_data	*data)
{
	console_msg(ANSI_RESET"\n"MSG_CLEAN_UP);
	console_msg(MSG_DESTROY_IMG_AND_WINDOW);
	mlx_destroy_image(data->mlx->conn, data->img->addr);
	mlx_destroy_window(data->mlx->conn, data->mlx->win);
	console_msg(MSG_DESTROY_SCENE);
	destroy_scene(data->scene);
	console_msg(ANSI_MAGENTA"\n"MSG_SHUTDOWN);
	exit(0);
}
