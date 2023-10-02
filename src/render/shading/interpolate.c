#include "render.h"

enum e_vertex
{
	A,
	B,
	C
};

static void	barycentric_coordinates(t_vec3 p, t_vec3 *abc, float *coord)
{
	const float	area_abc = vec3_length(\
				vec3_cross(vec3_sub(abc[B], abc[A]), vec3_sub(abc[C], abc[A])));
	const float	area_abp = vec3_length(\
				vec3_cross(vec3_sub(abc[B], abc[A]), vec3_sub(p, abc[A])));
	const float	area_acp = vec3_length(\
				vec3_cross(vec3_sub(abc[A], abc[C]), vec3_sub(p, abc[C])));
	const float	area_bcp = vec3_length(\
				vec3_cross(vec3_sub(abc[C], abc[B]), vec3_sub(p, abc[B])));

	coord[A] = area_bcp / area_abc;
	coord[B] = area_acp / area_abc;
	coord[C] = area_abp / area_abc;
}

/*
Returns the interpolated normal for smooth shading.
The ratio of the three vertices of the triangle to the
intersection point is calculated through the Barycentric coordinate system,
and a new normal interpolated at that ratio is obtained.
*/
t_vec3	interpolate_normal(t_vec3 p, t_triangle *t)
{
	float	ratio[3];

	barycentric_coordinates(p, t->vertices, ratio);
	return (vec3_interpolate(t->vertex_normals, ratio, 3));
}
