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
smooth shading을 위해 보간된 노말을 반환한다.
교차지점이 위치한 삼각형의 세 정점이 어떠한 비율로 교차지점에 반영되었는지
Barycentric(무게중심) 좌표계를 통해 구하고 해당 비율로 보간된 새로운 노말을 구한다.
*/
t_vec3	interpolate_normal(t_vec3 p, t_triangle *t)
{
	float	ratio[3];

	barycentric_coordinates(p, t->vertices, ratio);
	return (vec3_interpolate(t->vertex_normals, ratio, 3));
}
