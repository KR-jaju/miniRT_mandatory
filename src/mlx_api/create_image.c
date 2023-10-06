/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:07 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:08 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_api.h"

void	create_image(void *mlx_conn, t_image *img, int width, int height)
{
	img->addr = mlx_new_image(mlx_conn, width, height);
	img->data = mlx_get_data_addr(img->addr, &img->bits_per_pixel, \
								&img->bytes_per_line, &img->endian);
}
