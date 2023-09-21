
#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include "libmath.h"
# include "libds.h"


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
void	parse_a(t_scene *scene, int declared[3], const char **str_ref);
void	parse_c(t_scene *scene, int declared[3], const char **str_ref);
void	parse_l(t_scene *scene, int declared[3], const char **str_ref);
void	parse_sp(t_scene *scene, t_list *obj_list, const char **str_ref);
void	parse_pl(t_scene *scene, t_list *obj_list, const char **str_ref);
void	parse_cy(t_scene *scene, t_list *obj_list, const char **str_ref);

void	skip_space(const char **str_ref);
void	ensure_empty(char const *str);
t_vec3	parse_vec3(const char **str_ref);
float	parse_float(const char **str_ref);

#endif
