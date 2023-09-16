
#include "parser.h"
#include "scene.h"
#include "libft.h"


//t_scene, declared, str_ref : int
static
int	parse_line(const char *line, t_scene *scene, int declared[3])
{
	if (ft_strncmp(line, "A", 1))
		return (parse_a(scene, declared, line + 1));
	else if (ft_strncmp(line, "C", 1))
		return (parse_c(scene, declared, line + 1));
	else if (ft_strncmp(line, "L", 1))
		return (parse_c(scene, declared, line + 1));
	else if (ft_strncmp(line, "sp", 2))
		return (parse_sp(scene, declared, line + 2));
	else if (ft_strncmp(line, "pl", 2))
		return (parse_pl(scene, declared, line + 2));
	else if (ft_strncmp(line, "cy", 2))
		return (parse_cy(scene, declared, line + 2));
}

// TODO: 씬 파싱부 구현
// 변환 후 버텍스 좌표 및 노말을 위한 동적할당 여기서 해둘 것
t_scene	*parse_rt(int fd)
{
	t_scene*const	scene = malloc(sizeof(t_scene));
	int				declared[3];
	char			*line;

	ft_bzero(declared, sizeof(int) * 3);
	//scene_init(&scene);
	line = get_next_line(fd);
	while (line != (void *)0)
	{
		if (parse_line(line, &scene, declared) == -1)
			return ((void *)0);
		line = get_next_line(fd);
	}
	if (!declared[A] || !declared[C] || !declared[L])
		return ((void *)0);
	return (scene);
}
