#ifndef MLX_API_H
#define MLX_API_H

# include <stddef.h>
# include <mlx.h>
# include "libmath.h"

# define EVENT_KEY_PRESS	2
# define EVENT_DESTROY		17
# define KEY_ESC 			53

typedef struct s_mlx
{
	void	*conn;
	void	*win;
}t_mlx;

typedef struct s_image
{
	void	*addr;
	char	*data;
	size_t	data_size;
	int		width;
	int		height;
	float	aspect_ratio;
	int		n_pixels;
	int		bits_per_pixel;
	int		bytes_per_line;
	int		endian;
}t_image;

typedef struct s_pixel
{
	int		x;
	int		y;
	t_vec3	color;
}t_pixel;

int		keypress_hook(int keycode, void *param);
void	put_pixel_to_image(t_pixel p, t_image *img);
void 	create_image(void *mlx_conn, t_image *img, int width, int height);

#endif
