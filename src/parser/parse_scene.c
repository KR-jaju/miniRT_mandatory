/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:55 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:56 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "console.h"
#include "parser_internal.h"

int	parse_scene(t_scene *scene, const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_parse_error(ERROR_FILEOPEN);
	parse_rt(scene, fd);
	return (0);
}
