/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:05 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:06 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "console.h"

static bool	has_extension(const char *path, const char *ext)
{
	const size_t	path_len = ft_strlen(path);
	const size_t	ext_len = ft_strlen(ext);

	if (path_len <= ext_len)
		return (false);
	return (ft_strcmp(path + path_len - ext_len, ext) == 0);
}

/*
1. Parse scene and initialize
2. Rendering images in pixel by pixel using the scene
3. Put the completed image in the window so far

Repeat steps 2 and 3 until the rendering is complete.

Using the ray tracing method, rendering a single image can take a long time.
Even before everything is rendered, we want to put the image into the window 
continuously to check the status,
so register the render_to_window function in the loop_hook and run it repeatedly.
*/
int	main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_scene	scene;
	t_image	img;

	if (argc != 2 || has_extension(argv[1], ".rt") == false)
	{
		console_msg("Error\n"MSG_USAGE);
		return (1);
	}
	init_scene(&scene, argv[1]);
	init_mlx(&mlx);
	init_image(&img, mlx.conn);
	mlx_hook(mlx.win, EVENT_KEY_PRESS, 0, keypress_hook, \
				&(t_program_data){&mlx, &scene, &img});
	mlx_hook(mlx.win, EVENT_DESTROY, 0, shutdown_program, \
				&(t_program_data){&mlx, &scene, &img});
	mlx_loop_hook(mlx.conn, render_display, \
				&(t_program_data){&mlx, &scene, &img});
	console_start();
	mlx_loop(mlx.conn);
	return (0);
}
