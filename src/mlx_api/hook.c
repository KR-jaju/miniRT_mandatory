#include <stdlib.h>
#include "mlx_api.h"

int	keypress_hook(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_ESC)
	{
		// 동적 할당된 모든 리소스 해제
		exit(0);
	}
	return (0);
	
}
