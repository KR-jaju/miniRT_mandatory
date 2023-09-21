#include "libft.h"
#include "miniRT.h"
#include "mlx_api.h"

void	init_image(t_image *img, void *mlx_conn)
{
	img->addr = mlx_new_image(mlx_conn, IMAGE_WIDTH, IMAGE_HEIGHT);
	img->data = mlx_get_data_addr(img->addr, &img->bits_per_pixel, \
								&img->bytes_per_line, &img->endian);
	img->width = IMAGE_WIDTH;
	img->height = IMAGE_HEIGHT;
	img->aspect_ratio = img->width / img->height;
	img->n_pixels = img->width * img->height;
	img->data_size = img->bytes_per_line * img->height;
	ft_memset(img->data, 0, img->data_size);
}

// 차후 지역 static 변수에 가둬두는 방식 고려
void	init_mlx(t_mlx *mlx)
{
	mlx->conn = mlx_init();
	mlx->win = mlx_new_window(mlx->conn, \
								IMAGE_WIDTH, IMAGE_HEIGHT, WINDOW_TITLE);
}
