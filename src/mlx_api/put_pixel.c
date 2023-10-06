/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pixel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:09 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:10 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_api.h"
#include "libmath.h"
#include "miniRT.h"

static uint32_t	vec3_to_rgb(t_vec3 v)
{
	v.x = clamp(v.x, 0.0f, 1.0f);
	v.y = clamp(v.y, 0.0f, 1.0f);
	v.z = clamp(v.z, 0.0f, 1.0f);
	return ((int)(v.x * 255) << 16 | (int)(v.y * 255) << 8 | (int)(v.z * 255));
}

void	put_pixel_to_image(t_pixel p, t_image *img)
{
	char	*dst;
	int		offset;

	if (!(0 <= p.x && p.x <= img->width && 0 <= p.y && p.y <= img->height))
		return ;
	offset = (p.y * img->bytes_per_line) + (p.x * (img->bits_per_pixel / 8));
	if (0 <= offset && \
		offset < (img->width * img->height) * 4)
	{
		dst = &img->data[offset];
		*(uint32_t *)dst = vec3_to_rgb(p.color);
	}
}
