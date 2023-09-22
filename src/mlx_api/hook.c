#include "mlx_api.h"

int	shutdown_program(void *resource);

int	keypress_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_ESC)
		shutdown_program(param);
	return (0);
}
