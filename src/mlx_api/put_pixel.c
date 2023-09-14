#include "mlx_api.h"
#include "libmath.h"
#include "miniRT.h"

// vec3 컴포넌트 값이 1을 넘는 경우 발생시 clamp 연산 추가
static uint32_t	vec3_to_rgb(t_vec3 v)
{
	return ((int)v.x << 16 | (int)v.y << 8 | (int)v.z);
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
