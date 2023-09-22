#include "libft.h"
#include "mlx_api.h"
#include "scene.h"
#include "parser.h"
#include "console.h"
#include "settings.h"

int	preprocess_scene(t_scene *scene);

static void	init_meshs(t_mesh *meshs)
{
	const int	parms[3][2] = {\
	[MESH_SPHERE] = {10, 10},
	[MESH_PLANE] = {-1, -1},
	[MESH_CYLINDER] = {10, -1},
	};

	// TODO: 해상도(RESOLUTION)값에 따른 섹터, 스택 개수 계산식 조율
	sphere_init(&meshs[MESH_SPHERE], \
				RESOLUTION * parms[MESH_SPHERE][0], \
				RESOLUTION * parms[MESH_SPHERE][1]);
	plane_init(&meshs[MESH_PLANE]);
	cylinder_init(&meshs[MESH_CYLINDER], \
				RESOLUTION * parms[MESH_CYLINDER][0]);
}

void	init_scene(t_scene *scene, const char *path)
{
	init_meshs(scene->meshs);
	parse_scene(scene, path);
	if (preprocess_scene(scene) == -1)
	{
		console_msg(MSG_ERROR_MALLOC);
		exit(1);
	}
}

void	init_mlx(t_mlx *mlx)
{
	mlx->conn = mlx_init();
	mlx->win = mlx_new_window(mlx->conn, \
								IMAGE_WIDTH, IMAGE_HEIGHT, WINDOW_TITLE);
}

void	init_image(t_image *img, void *mlx_conn)
{
	create_image(mlx_conn, img, IMAGE_WIDTH, IMAGE_HEIGHT);
	img->width = IMAGE_WIDTH;
	img->height = IMAGE_HEIGHT;
	img->aspect_ratio = img->width / img->height;
	img->n_pixels = img->width * img->height;
	img->data_size = img->bytes_per_line * img->height;
	ft_memset(img->data, 0, img->data_size);
}