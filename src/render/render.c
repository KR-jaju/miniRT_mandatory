#include <stdio.h>
#include "libft.h"
#include "mlx.h"
#include "libmath.h"
#include "miniRT.h"
#include "render.h"
#include "mlx_api.h"
#include "console.h"
#include "settings.h"
#include "debug.h"

t_vec3	render_pixel(int x, int y, t_scene *scene, t_image *img);

/*
1. 현재 처리해야하는 픽셀 컬러 계산
2. 계산된 픽셀 이미지에 반영
3. 이미지를 윈도우에 put
*/
void	render_image(int progress, t_scene *scene, t_image *img, bool *done)
{
	t_pixel	p;

	p.y = progress / img->width;
	p.x = progress - (p.y * img->width);
	p.color = render_pixel(p.x, p.y, scene, img);
	put_pixel_to_image(p, img);
	if (progress == img->n_pixels)
		*done = true;
}

// TODO: 현재는 window에 put하는 작업과 콘솔 출력을 이 함수에서 전부 하고 있는데
// 차후 render_loop 함수 별도로 만들어 render_display 함수 호출 + 콘솔 출력 
int	render_display(t_program_data *data)
{
	static bool	done = false;
	static int	progress = 0;

	if (done)
		return (0);
	if (progress == 0)
		console_msg(MSG_RENDER_START"\n"MSG_RENDER_PROGRESS);
	render_image(progress, data->scene, data->img, &done);
	if (progress % 5000 == 0 || done)
	{
		mlx_put_image_to_window(data->mlx->conn,
								data->mlx->win, data->img->addr, 0, 0);
		printf("progress: %d / %d\n", progress, data->img->n_pixels);
	}
	progress++;
	if (done)
		console_msg(MSG_RENDER_DONE);
	return (0);
}
