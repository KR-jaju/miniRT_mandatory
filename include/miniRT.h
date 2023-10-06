/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:06:17 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:06:18 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "mlx_api.h"
# include "scene.h"
// # include "debug.h" // for dev

typedef struct s_program_data
{
	t_mlx	*mlx;
	t_scene	*scene;
	t_image	*img;
}t_program_data;

void	init_scene(t_scene *scene, const char *path);
void	init_mlx(t_mlx *mlx);
void	init_image(t_image *img, void *mlx_conn);
int		render_display(t_program_data *data);
int		shutdown_program(t_program_data	*data);

#endif
