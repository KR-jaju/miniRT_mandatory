#include "mlx_api.h"

int	shutdown_program(void *data);

int	keypress_hook(int keycode, void *data)
{
	if (keycode == KEY_ESC)
		shutdown_program(data);
	return (0);
}
