
#include "libft.h"
#include "render.h"

static bool	is_point_in_triangle(t_vec3 p, t_vec3 *triangle)
{
	// TODO: 삼각형 내부에 교차지점이 있는지 확인 (CPP02 마지막 문제와 같이 외적 사용)
	(void)p;
	(void)triangle;
	return (true);
}

/*
레이-폴리곤(삼각형) 교차 검사:
	1. 삼각형의 평면과 레이가 교차하는지 확인한다
	2. 만약 그렇다면, 그 교차지점이 삼각형 내부에 있는지 확인한다

평면: (p-p0) * n = 0
레이: l0 + l * t = p

두 식을 연립하면 t = (p0 - l0) * n / (l * n)
n과 l이 평행할 시, 즉 평면과 직선이 수직할시 값은 무한대에 가까워짐
*/
bool	ray_polygon_intersection(t_ray *ray, t_polygon *polygon, \
									t_hit_record *record)
{
	const float	dot_nl = vec3_dot(ray->dir, polygon->normal);
	float		t;
	t_vec3		p;

	if ((0 < dot_nl && dot_nl < EPSILON) || dot_nl < 0)
		return (false);
	t = vec3_dot(\
	vec3_sub(polygon->vertex[0], ray->origin), polygon->normal) / dot_nl;
	if (t < 0)
		return (false);
	p = vec3_add(ray->origin, vec3_mul(ray->dir, t));
	if (is_point_in_triangle(p, polygon->vertex) == false)
		return (false);
	record->polygon = polygon;
	record->point = p;
	record->t = t;
	return (true);
}

//TODO: closest_hit 없어도 안 헷갈릴 것 같으면 record 대체하고 불필요한 연산 줄이기
/*
레이-오브젝트 교차 검사:
오브젝트의 모든 폴리곤을 돌며 가장 가까운 hit을 찾는다.
*/
bool	ray_object_intersection(t_ray *ray, t_object *object, \
								t_hit_record *record)
{
	t_polygon		*polygon;
	t_hit_record	hit;
	t_hit_record	closest_hit;

	closest_hit.t = INFINITY;
	polygon = &object->mesh->polygons[0];
	while (polygon)
	{
		if (ray_polygon_intersection(ray, polygon, &hit) == true \
			&& hit.t < closest_hit.t)
			ft_memcpy(&closest_hit, &hit, sizeof(t_hit_record));
		polygon++;
	}
	if (closest_hit.t == INFINITY)
		return (false);
	else
	{
		ft_memcpy(record, &closest_hit, sizeof(t_hit_record));
		return (true);
	}
}
