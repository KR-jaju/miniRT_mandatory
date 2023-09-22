#include "mlx_api.h"

void	create_image(void *mlx_conn, t_image *img, int width, int height)
{
	img->addr = mlx_new_image(mlx_conn, width, height);
	img->data = mlx_get_data_addr(img->addr, &img->bits_per_pixel, \
								&img->bytes_per_line, &img->endian);
}
