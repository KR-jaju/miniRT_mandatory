#ifndef DEBUG_H
#define DEBUG_H

# include <stdio.h>
# include "libmath.h"
# include "scene.h"

int		dummy_scene(t_scene *scene);
void	print_scene(t_scene *scene);
void	print_vec3(t_vec3 v);
void	print_vec4(t_vec4 v);
void	print_mat4(t_mat4 m);
int		radian_to_degree(float r);

#endif
