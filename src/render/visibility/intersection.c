#include "libft.h"
#include "render.h"
#include "settings.h"

/*
삼각형의 세 점 a, b, c는 한 평면 안에 놓여있기 때문에,
cross_abap, cross_bcbp, cross_cacp는 단 두 가지의 방향만 갖게 됨
(해당 평면을 기준으로 법선벡터 2종류)
따라서 세 외적벡터의 방향이 같은지 확인할 때 두 번만 확인해도 무방
*/
static bool	is_point_in_triangle(t_vec3 p, t_vec3 *tp)
{
	const t_vec3	cross_abap = vec3_cross(vec3_sub(tp[1], tp[0]), \
											vec3_sub(p, tp[0]));
	const t_vec3	cross_bcbp = vec3_cross(vec3_sub(tp[2], tp[1]), \
											vec3_sub(p, tp[1]));
	const t_vec3	cross_cacp = vec3_cross(vec3_sub(tp[0], tp[2]), \
											vec3_sub(p, tp[2]));

	return (vec3_dot(cross_abap, cross_bcbp) >= 0 \
			&& vec3_dot(cross_abap, cross_cacp) >= 0);
}

/*
레이-폴리곤(삼각형) 교차 검사:
	1. 삼각형의 평면과 레이가 교차하는지 확인한다
	2. 만약 그렇다면, 그 교차지점이 삼각형 내부에 있는지 확인한다

평면: (p-p0) * n = 0
레이: l0 + l * t = p
두 식을 연립하면 t = (p0 - l0) * n / (n * l)

- n과 l의 방향이 같을 시(n * l > 0), 즉 레이가 평면의 뒷면과 교차하는 경우 false
- n과 l이 평행할 시(n * l = 0), 즉 평면과 직선이 수직할시 false
*/
bool	ray_triangle_intersection(t_ray *ray, t_triangle *tri, \
									t_hit_record *record)
{
	const float	dot_nl = vec3_dot(ray->dir, tri->face_normal);
	float		t;
	t_vec3		point;

	if (dot_nl > 0 || (-EPSILON < dot_nl && dot_nl < 0))
		return (false);
	t = vec3_dot(vec3_sub(tri->vertices[0], ray->origin), tri->face_normal) \
																/ dot_nl;
	if (t < 0)
		return (false);
	point = vec3_add(ray->origin, vec3_mul(ray->dir, t));
	if (is_point_in_triangle(point, tri->vertices) == false)
		return (false);
	record->t = t;
	record->point = point;
	record->triangle = tri;
	return (true);
}

/*
레이-오브젝트 교차 검사:
오브젝트의 모든 폴리곤을 돌며 가장 가까운 hit을 찾는다.
*/
bool	ray_object_intersection(t_ray *ray, t_object *object, \
								t_hit_record *record)
{
	t_hit_record	hit;
	t_hit_record	closest_hit;
	int				i;

	closest_hit.t = INFINITY;
	i = 0;
	while (i < object->mesh->n_triangles)
	{
		if (ray_triangle_intersection(ray, &object->triangles[i], &hit) == true \
			&& hit.t < closest_hit.t)
			ft_memcpy(&closest_hit, &hit, sizeof(t_hit_record));
		i++;
	}
	if (closest_hit.t == INFINITY)
		return (false);
	ft_memcpy(record, &closest_hit, sizeof(t_hit_record));
	record->material = &object->material;
	return (true);
}
