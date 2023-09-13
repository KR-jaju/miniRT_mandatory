#ifndef RENDER_H
#define RENDER_H

# include <stdbool.h>
# include "libmath.h"
# include "scene.h"
# include "mlx_api.h"

// default material
# define REFLECTIVITY	0.3
# define K_DIFFUSE		0.3
# define K_SPECULAR		0.3
# define SHININESS		0.3

// default camera parameter
# define NEAR	0.3
# define FAR	1000

typedef struct s_polygon
{
	t_vec3		vertex[3];
	t_vec3		normal;
}t_polygon;

typedef struct s_material
{
	t_vec3	color;
	float	reflectivity;
	float	k_diffuse;
	float	k_specular;
	float	shininess;
}t_material;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}t_ray;

typedef struct s_hit_record
{
	t_vec3		point;
	t_vec3		normal;
	t_vec3		color;
	float		t; // 카메라 레이 디렉션 스칼라
}t_hit_record;

// render main logic
t_vec3	compute_pixel_color(int x, int y, t_scene *scene, t_image *img);
t_vec3	shade_intersection(const t_hit_record *hit, const t_scene *scene);
bool	ray_object_intersection(t_ray *ray, t_object *object, \
								t_hit_record *record);

// direction
t_vec3	incident_direction(t_vec3 hit_pos, t_vec3 light_pos);
t_vec3	reflection_direction(t_vec3 i, t_vec3 n);
t_vec3	view_direction(t_vec3 camera_pos, t_vec3 hit_pos);

// matrix
t_mat4	model_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale);
t_mat4	view_matrix(t_vec3 eye, t_vec3 look_at, t_vec3 up);
t_mat4	projection_matrix(float fov, float aspect_ratio, float near, float far);

#endif 
