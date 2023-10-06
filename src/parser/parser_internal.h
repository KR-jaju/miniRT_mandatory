/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:03 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:04 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_INTERNAL_H
# define PARSER_INTERNAL_H

# include "libds.h"
# include "scene.h"
# include "console.h"

enum	e_mandatory_element
{
	A = 0,
	C,
	L
};

void	parse_rt(t_scene *scene, const int fd);

// parse element
void	parse_a(t_scene *scene, bool declared[3], const char **str_ref);
void	parse_c(t_scene *scene, bool declared[3], const char **str_ref);
void	parse_l(t_scene *scene, bool declared[3], const char **str_ref);
void	parse_sp(t_scene *scene, t_list *obj_list, const char **str_ref);
void	parse_pl(t_scene *scene, t_list *obj_list, const char **str_ref);
void	parse_cy(t_scene *scene, t_list *obj_list, const char **str_ref);

// parse number
t_vec3	parse_vec3(const char **str_ref);
float	parse_float(const char **str_ref);

// utils
void	skip_space(const char **str_ref);
void	ensure_empty(const char *str);
t_vec3	rgb_to_vec3(t_vec3 color);

/* ------------------ HANDLE ERROR ------------------- */

enum e_parse_error
{
	ERROR_MALLOC,
	ERROR_FILEOPEN,
	ERROR_INVALID_LINE_FORMAT,
	ERROR_DUPLIATE_DECLARED,
	ERROR_MANDATORY_NOT_EXIST,
};

int		parser_line_count(int mode);
# define COUNT_UP 0
# define FETCH_COUNT 1

void	handle_parse_error(int errcode);

#endif
