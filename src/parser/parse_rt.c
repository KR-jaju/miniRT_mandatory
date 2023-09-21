
#include "parser.h"
#include "scene.h"
#include "libft.h"
#include "libds.h"


//t_scene, declared, str_ref : int
static
void	parse_line(const char *line, t_list *obj_list, t_scene *scene, int declared[3])
{
	if (ft_strncmp(line, "A", 1) == 0)
		return (parse_a(scene, declared, &line));
	else if (ft_strncmp(line, "C", 1))
		return (parse_c(scene, declared, &line));
	else if (ft_strncmp(line, "L", 1))
		return (parse_l(scene, declared, &line));
	else if (ft_strncmp(line, "sp", 2))
		return (parse_sp(scene, obj_list, &line));
	else if (ft_strncmp(line, "pl", 2))
		return (parse_pl(scene, obj_list, &line));
	else if (ft_strncmp(line, "cy", 2))
		return (parse_cy(scene, obj_list, &line));
	else
		ensure_empty(line);
}

// TODO: 씬 파싱부 구현
// 변환 후 버텍스 좌표 및 노말을 위한 동적할당 여기서 해둘 것
// 아직 에러 메세지 표시는 없음
void	parse_rt(t_scene *scene, const int fd)
{
	t_list	object_list;
	int		declared[3];
	char	*line;

	list_init(&object_list, sizeof(t_object), 8);
	ft_bzero(declared, sizeof(int) * 3);
	//scene_init(&scene);
	line = get_next_line(fd);
	while (line != (void *)0)
	{
		parse_line(line, &object_list, scene, declared);
		line = get_next_line(fd);
	}
	if (!declared[A] || !declared[C] || !declared[L])
		exit(1);
	scene->objects = list_collect(&object_list, (uint32_t *)&scene->n_objects);
	//TODO: free list
}
