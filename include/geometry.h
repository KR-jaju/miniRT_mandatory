#ifndef GEOMETRY_H
#define GEOMETRY_H

# include <math.h>
# define EPSILON 1e-8

/* -------------------------- STRUCT DECLARATIONS --------------------------- */

typedef struct s_vector3
{
	float	x;
	float	y;
	float	z;
}	t_vector3;

typedef struct s_vector4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vector4;

typedef struct s_matrix3 {
	t_vector3	v1;
	t_vector3	v2;
	t_vector3	v3;
}	t_matrix3;

typedef struct s_matrix4 {
	t_vector4	v1;
	t_vector4	v2;
	t_vector4	v3;
	t_vector4	v4;
}	t_matrix4;

typedef t_vector3	t_vec3;
typedef t_vector4	t_vec4;
typedef t_matrix3	t_mat3;
typedef t_matrix4	t_mat4;

/* -------------------------- FUNCTION PROTOTYPES --------------------------- */

// vector3
t_vector3	vec3(float x, float y, float z);
t_vector3	vec3_add(t_vector3 v1, t_vector3 v2);
t_vector3	vec3_sub(t_vector3 v1, t_vector3 v2);
float		vec3_dot(t_vector3 v1, t_vector3 v2);
t_vector3	vec3_cross(t_vector3 v1, t_vector3 v2);
float		vec3_length(t_vector3 v);

// vector4
t_vector4	vec4(float x, float y, float z, float w);
t_vector4	vec4_add(t_vector4 v1, t_vector4 v2);
t_vector4	vec4_sub(t_vector4 v1, t_vector4 v2);
float		vec4_dot(t_vector4 v1, t_vector4 v2);
float		vec4_length(t_vector4 v);

// matrix
t_matrix4	unit_mat4(void);
t_matrix4	mat4_mul(t_matrix4 m1, t_matrix4 m2);

// transform
t_vector3	mat4_mul_vec3(t_matrix4 m, t_vector3 v);
t_vector4	mat4_mul_vec4(t_matrix4 m, t_vector4 v);
void		compose_scale_mat4(t_matrix4 *m, float x, float y, float z);
void		compose_rotate_mat4(t_matrix4 *m, float x, float y, float z);
void		compose_move_mat4(t_matrix4 *m, float x, float y, float z);

#endif
