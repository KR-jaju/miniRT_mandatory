#ifndef RENDER_H
#define RENDER_H

# include <stdbool.h>
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
t_vec3	get_camera_ray(t_camera *camera);
bool	intersection_check(t_object *object, t_ray cam_ray, \
							t_hit_record *hit_record);
t_vec3	calculate_intersection_color(t_object *object, t_scene *scene);

#endif