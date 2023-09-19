
#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include "libmath.h"


# define A 0
# define C 1
# define L 2


void	parse_a(t_scene *scene, int declared[3], const char **str_ref);
void	parse_c(t_scene *scene, int declared[3], const char **str_ref);
void	parse_l(t_scene *scene, int declared[3], const char **str_ref);
void	parse_sp(t_scene *scene, int declared[3], const char **str_ref);
void	parse_pl(t_scene *scene, int declared[3], const char **str_ref);
void	parse_cy(t_scene *scene, int declared[3], const char **str_ref);


void	skip_space(const char **str_ref);
void	line_end(const char **str_ref);
t_vec3	parse_vec3(const char **str_ref);
float	parse_float(const char **str_ref);

#endif
