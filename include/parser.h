
#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include "libmath.h"
# include "libds.h"
# include "debug.h"
# include "console.h"

# define A 0
# define C 1
# define L 2

enum	e_mesh_type
{
	MESH_SPHERE = 0,
	MESH_PLANE,
	MESH_CYLINDER
};

void	parse_rt(t_scene *scene, const int fd);

// parse element
void	parse_a(t_scene *scene, int declared[3], const char **str_ref);
void	parse_c(t_scene *scene, int declared[3], const char **str_ref);
void	parse_l(t_scene *scene, int declared[3], const char **str_ref);
void	parse_sp(t_scene *scene, t_list *obj_list, const char **str_ref);
void	parse_pl(t_scene *scene, t_list *obj_list, const char **str_ref);
void	parse_cy(t_scene *scene, t_list *obj_list, const char **str_ref);

// parse number
t_vec3	parse_vec3(const char **str_ref);
float	parse_float(const char **str_ref);

// utils
void	skip_space(const char **str_ref);
void	ensure_empty(char const *str);

/* ------------------ HANDLE ERROR ------------------- */

enum e_parse_error
{
	ERROR_FILEOPEN,
	ERROR_INVALID_LINE_FORMAT,
	ERROR_DUPLIATE_DECLARED,
	ERROR_MANDATORY_NOT_EXIST,
};

# define MSG_ERROR_FILEOPEN "file open failed"
# define MSG_ERROR_INVALID_LINE_FORMAT "invalid line format"
# define MSG_ERROR_DUPLIATE_DECLARED "duplicate declared"
# define MSG_ERROR_MANDATORY_NOT_EXIST "mandatory element not exist in scene"

# define COUNT_UP 0
# define FETCH_COUNT 1

int		parser_count_state(int mode);
void	handle_parse_error(int errcode);

#endif
