#include "miniRT.h"
#include "render.h"
#include "mlx_api.h"

/*
1. 현재 처리해야하는 픽셀 컬러 계산
2. 계산된 픽셀 이미지에 반영
3. 이미지를 윈도우에 put
*/

int	render_to_window(t_program_data *data)
{
	const t_mlx		*mlx = data->mlx;
	const t_scene	*scene = data->scene;
	const t_image	*img = data->img;
	t_pixel			p;

	if (img->progress == img->n_pixels)
		return (0);
	p.y = (img->progress + 1) / img->width;
	p.x = img->progress - (p.y * img->height);
	p.color = calculate_pixel_color(p.x, p.y, scene);
	put_pixel_to_image(img, p);
	mlx_put_image_to_window(mlx->conn, mlx->win, img->addr, 0, 0);
}
