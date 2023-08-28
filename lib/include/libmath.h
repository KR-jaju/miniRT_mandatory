#ifndef LIBMATH_H
#define LIBMATH_H

# define EPSILON 1e-8

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

#endif
