#ifndef RENDER_H
#define RENDER_H

# include "libmath.h"
# include "scene.h"

t_vec3	calculate_pixel_color(int x, int y, t_scene *scene);

#endif