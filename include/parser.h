
#ifndef PARSER_H
# define PARSER_H

# include "scene.h"
# include "libmath.h"

typedef int	(*t_command)(t_scene *, int[3], const char**);


# define A 0
# define C 1
# define L 2


int		parse_c(t_scene *scene, int declared[3], const char **str_ref);
int		parse_a(t_scene *scene, int declared[3], const char **str_ref);


void	skip_space(const char **str_ref);
void	line_end(const char **str_ref);
t_vec3	parse_vec3(const char **str_ref);
float	parse_float(const char **str_ref);

#endif
