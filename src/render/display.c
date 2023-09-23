#include <stdio.h>
#include "miniRT.h"
#include "mlx_api.h"
#include "render.h"
#include "console.h"
#include "settings.h"

t_vec3	render_pixel(int x, int y, t_scene *scene, t_image *img);

void	render_image(int progress, t_scene *scene, t_image *img)
{
	t_pixel	p;

	p.y = progress / img->width;
	p.x = progress - (p.y * img->width);
	p.color = render_pixel(p.x, p.y, scene, img);
	put_pixel_to_image(p, img);
}

/*
1. 현재 처리해야하는 픽셀 컬러 계산
2. 계산된 픽셀 이미지에 반영
3. 이미지를 윈도우에 put
*/
int	render_display(t_program_data *data)
{
	static const int	interval = (IMAGE_WIDTH * IMAGE_HEIGHT) \
									* IMAGE_PUT_INTERVAL_PERCENT / 100;
	static int			progress = 0;

	if (progress >= data->img->n_pixels)
		return (0);
	render_image(progress, data->scene, data->img);
	progress++;
	if (progress % interval == 0 || progress == data->img->n_pixels)
	{
		mlx_put_image_to_window(data->mlx->conn, \
								data->mlx->win, data->img->addr, 0, 0);
		printf(ANSI_CYAN"progress: %d / %d (%.2f%%)\n"ANSI_RESET, \
								progress, data->img->n_pixels, \
								(float)progress / data->img->n_pixels * 100);
	}
	if (progress == data->img->n_pixels)
		console_finish();
	return (0);
}
