#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"

void	parse_rt(t_scene *scene, const int fd);
 
int	parse_scene(t_scene *scene, const char *path)
{
	int fd;
	
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		// TODO: 차후 console 함수로 변경
		printf("File cannot opened\n");
		exit(1);
	}
	parse_rt(scene, fd);
	return (0);
}
