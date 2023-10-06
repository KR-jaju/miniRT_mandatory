/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:13 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:14 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
1. Calculating pixel colors that need to be processed at this time
2. Reflect calculated pixel color to image
3. Put the image into the window

Putting an image into a window takes a lot of time, 
so put operation is done at intervals
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
