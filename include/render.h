#ifndef RENDER_H
#define RENDER_H

# include <stdbool.h>
# include "libmath.h"
# include "scene.h"
# include "mlx_api.h"

typedef struct s_material
{
	t_vec3	color;
	float	k_diffuse;
	float	k_specular;
	float	shininess;
	float	reflectivity;
}t_material;

// TODO: 레이의 구성요소에 컬러를 둘지 차후 결정
typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
	t_vec3	color;
}t_ray;

typedef struct s_hit_record
{
	t_object	*object;
	t_polygon	*polygon;
	float		t; // 카메라 레이 디렉션 스칼라
}t_hit_record;

t_vec3	compute_pixel_color(int x, int y, t_scene *scene, t_image *img);
t_vec3	shade_intersection(t_hit_record *hit, t_scene *scene);
t_vec3	camera_ray_direction(int x, int y, t_camera *cam, t_image *img);
bool	ray_object_intersection(t_ray *ray, t_object *object, \
								t_hit_record *record);

// direction
t_vec3	incident_direction(t_vec3 hit_pos, t_vec3 light_pos);
t_vec3	reflection_direction(t_vec3 i, t_vec3 n);
t_vec3	view_direction(t_vec3 camera_pos, t_vec3 hit_pos);



#endif 
