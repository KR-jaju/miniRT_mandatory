/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:06:07 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:06:08 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
# define LIBMATH_H

# include <math.h>
# include <stdbool.h>

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

// column-major
typedef union s_mat4 {
	float	e[4][4];
	t_vec4	col[4];
}	t_mat4;

/* -------------------------- FUNCTION PROTOTYPES --------------------------- */

// zero
bool		is_zero(float n);

// vector3
t_vec3		vec3(float x, float y, float z);
t_vec3		vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_mul(t_vec3 v, float a);
float		vec3_dot(t_vec3 v1, t_vec3 v2);
t_vec3		vec3_hadamard(t_vec3 v1, t_vec3 v2);
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
t_vec3		vec3_interpolate(t_vec3 *vectors, float *ratio, int n_vectors);

// matrix4
t_mat4		mat4_identity(void);
t_mat4		mat4_by_values(const float values[]);
t_mat4		mat4_mulmm(t_mat4 a, t_mat4 b);
t_mat4		mat4_transpose(t_mat4 m);
float		mat4_determinant(t_mat4	m);
float		mat4_cofactor(t_mat4 m, int row, int column);
t_mat4		mat4_inverse(t_mat4 m);

// transform
t_vec4		mat4_mulmv(t_mat4 m, t_vec4 v);

// clamp
float		clamp(float a, float min, float max);

#endif
