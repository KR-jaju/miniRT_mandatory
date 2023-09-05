#ifndef LIBMATH_H
#define LIBMATH_H

# include <math.h>
# define EPSILON 1e-8

/* -------------------------- STRUCT DECLARATIONS --------------------------- */

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_vec4
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_vec4;

typedef struct s_mat3 {
	t_vec3	v1;
	t_vec3	v2;
	t_vec3	v3;
}	t_mat3;

typedef struct s_mat4 {
	t_vec4	v1;
	t_vec4	v2;
	t_vec4	v3;
	t_vec4	v4;
}	t_mat4;

/* -------------------------- FUNCTION PROTOTYPES --------------------------- */

// vector3
t_vec3		vec3(float x, float y, float z);
t_vec3		vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_mul(t_vec3 v, float a);
float		vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_cross(t_vec3 v1, t_vec3 v2);
float		vec3_length(t_vec3 v);
t_vec3		vec3_normalize(t_vec3 v);

// vector4
t_vec4		vec4(float x, float y, float z, float w);
t_vec4		vec4_add(t_vec4 v1, t_vec4 v2);
t_vec4		vec4_sub(t_vec4 v1, t_vec4 v2);
t_vec4		vec4_mul(t_vec4 v, float a);
float		vec4_dot(t_vec4 v1, t_vec4 v2);
float		vec4_length(t_vec4 v);
t_vec4		vec4_normalize(t_vec4 v);

// matrix
t_mat4		unit_mat4(void);
t_mat4		mat4_mulmm(t_mat4 m1, t_mat4 m2);
t_mat4		mat4_inverse(t_mat4 m);

// transform
t_vec4		mat4_mulmv(t_mat4 m, t_vec4 v);
void		compose_scale_mat4(t_mat4 *m, float x, float y, float z);
void		compose_rotate_mat4(t_mat4 *m, float x, float y, float z);
void		compose_move_mat4(t_mat4 *m, float x, float y, float z);

#endif
