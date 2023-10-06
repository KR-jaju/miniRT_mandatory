/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shutdown.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:03 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:18:03 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "miniRT.h"
#include "mlx_api.h"
#include "mesh.h"
#include "console.h"

static void	destroy_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < MESH_COUNT)
	{
		free(scene->meshes[i].vertices);
		free(scene->meshes[i].vertex_normals);
		free(scene->meshes[i].indices);
		i++;
	}
	i = 0;
	while (i < scene->n_objects)
	{
		free(scene->objects[i].vertices);
		free(scene->objects[i].vertex_normals);
		free(scene->objects[i].triangles);
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
	console_msg(ANSI_MAGENTA"\n"MSG_SHUTDOWN""ANSI_RESET);
	exit(0);
}
