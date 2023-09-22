#include <stdbool.h>
#include <stdio.h>
#include <mlx.h>
#include "libft.h"
#include "miniRT.h"
#include "console.h"
#include "mlx_api.h"
#include "console.h"

// TODO: 메모리 할당 예외처리

/*
1. scene 파싱 작업 및 initialize
2. scene의 정보를 사용해 image를 렌더링
3. window에 image를 put

렌더링이 전부 완료되기 전까지 2,3의 과정을 반복한다.

ray tracing 방식을 사용하므로 단 하나의 이미지를 렌더링하는데도 시간이 오래 걸릴 수 있다.
전부 다 렌더링되기 이전에도 window에 image를 지속적으로 put하여 현황을 확인하게끔 하고 싶으므로
loop_hook에 render_to_window 함수를 등록하여 반복 실행한다.
*/

static bool	has_extension(const char *path, const char *ext)
{
	const size_t	path_len = ft_strlen(path);
	const size_t	ext_len = ft_strlen(ext);

	if (path_len <= ext_len)
		return (false);
	return (ft_strcmp(path + path_len - ext_len, ext) == 0);
}

int	main(int argc, char *argv[])
{
	t_mlx	mlx;
	t_scene	scene;
	t_image	img;

	if (argc != 2 || has_extension(argv[1], ".rt") == false)
	{
		printf("Error\n"MSG_USAGE"\n");
		return (1);
	}
	// dummy_scene(&scene);
	parse_scene(&scene, argv[1]);
	preprocess_scene(&scene);
	init_mlx(&mlx);
	init_image(&img, mlx.conn);
	mlx_hook(mlx.win, EVENT_KEY_PRESS, 0, keypress_hook, &scene);
	mlx_hook(mlx.win, EVENT_DESTROY, 0, shutdown_program, &scene);
	mlx_loop_hook(mlx.conn, render_display, \
				&(t_program_data){&mlx, &scene, &img});
	mlx_loop(mlx.conn);
	return (0);
}
