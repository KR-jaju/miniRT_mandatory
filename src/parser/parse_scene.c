#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "console.h"
#include "parser.h"

int	parse_scene(t_scene *scene, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_parse_error(ERROR_FILEOPEN);
	parse_rt(scene, fd);
	return (0);
}
