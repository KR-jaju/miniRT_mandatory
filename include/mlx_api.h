#ifndef MLX_API_H
#define MLX_API_H

# include "mlx.h"
# include "libmath.h"
# include "stddef.h"

# define EVENT_KEY_PRESS	2
# define EVENT_DESTROY		17
# define KEY_ESC 			53

# define WINDOW_WIDTH	800
# define WINDOW_HEIGHT	600

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

void	init_image(t_image *img, void *mlx_conn);
void	init_mlx(t_mlx *mlx);
int		keypress_hook(int keycode, void *param);
void	put_pixel_to_image(t_pixel p, t_image *img);

#endif
