#ifndef RENDER_H
#define RENDER_H

# include "libmath.h"
# include "scene.h"

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}t_ray;

typedef struct s_hit_record
{
	t_object	*object;
	float		t; // 카메라 레이 디렉션 스칼라
}t_hit_record;

t_vec3	calculate_pixel_color(int x, int y, t_scene *scene);

#endif