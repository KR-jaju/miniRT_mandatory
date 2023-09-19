#ifndef RENDER_H
#define RENDER_H

# include <stdbool.h>
# include "libmath.h"
# include "scene.h"
# include "mlx_api.h"
# include "render.h"

// default camera parameter
// 사실 아무 값이나 상관없다.
# define NEAR	0.3
# define FAR	1000

enum e_vertex
{
	A,
	B,
	C
};

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	dir;
}t_ray;

typedef struct s_hit_record
{
	float		t; // 카메라 레이 디렉션 스칼라
	t_vec3		point;
	t_triangle	*triangle;
	t_vec3		normal;
	t_material	*material;
}t_hit_record;

// direction
t_vec3	incident_direction(t_vec3 hit_pos, t_vec3 light_pos);
t_vec3	reflection_direction(t_vec3 i, t_vec3 n);
t_vec3	view_direction(t_vec3 camera_pos, t_vec3 hit_pos);

// TRS matrix
t_mat4	translate_matrix(t_vec3 t);
t_mat4	rotate_matrix(t_vec3 r);
t_mat4	scale_matrix(t_vec3 s);

// MVP matrix
t_mat4	model_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale);
t_mat4	view_matrix(t_vec3 eye, t_vec3 look_at, t_vec3 up);
t_mat4	projection_matrix(float fov, float aspect_ratio, float near, float far);

// intersection
bool	ray_triangle_intersection(t_ray *ray, t_triangle *tri, \
									t_hit_record *record);
bool	ray_object_intersection(t_ray *ray, t_object *object, \
								t_hit_record *record);

// phong
t_vec3	diffuse_reflection_value(const t_material *material, \
										t_vec3 ray_color, \
										t_vec3 incident, t_vec3 normal);
t_vec3	specular_reflection_value(const t_material *material, \
										t_vec3 ray_color, \
										t_vec3 reflection, t_vec3 view);
// interpolate
t_vec3	interpolate_normal(t_vec3 p, t_triangle *t);

#endif 
