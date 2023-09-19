#include <stdlib.h>
#include "miniRT.h"
#include "console.h"

int	shutdown_program(void *resource)
{
	// TODO: 할당된 메모리 해제
	(void)resource;
	console_msg(ANSI_BLUE""MSG_SHUTDOWN);
	exit(0);
}
