
#include "libft.h"
#include "render.h"
#include "debug.h"

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

// TODO: 매 픽셀 색상 계산시마다 불필요하게 폴리곤 정보를 채우고 있는 부분 최적화
static void	fill_polygon_info(int nth, t_object *object, t_polygon *polygon)
{
	const t_vec3	*vertices = object->vertices;
	const t_vec3	*normals = object->normals;
	const int		idx1 = object->mesh->indices[nth * 3];
	const int		idx2 = object->mesh->indices[nth * 3 + 1];
	const int		idx3 = object->mesh->indices[nth * 3 + 2];

	polygon->vertex[0] = vertices[idx1];
	polygon->vertex[1] = vertices[idx2];
	polygon->vertex[2] = vertices[idx3];
	polygon->normal = vec3_mul(\
						vec3_add(vec3_add(normals[idx1], normals[idx2]), \
											normals[idx3]), (float)1 / 3);
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

	if (is_zero(dot_nl) || dot_nl > 0)
		return (false);
	t = vec3_dot(vec3_sub(polygon->vertex[0], ray->origin), polygon->normal) \
																/ dot_nl;
	if (t < 0)
		return (false);
	p = vec3_add(ray->origin, vec3_mul(ray->dir, t));
	if (is_point_in_triangle(p, polygon->vertex) == false)
		return (false);
	record->point = p;
	record->normal = polygon->normal;
	record->t = t;
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
	t_polygon		polygon;
	int				i;

	closest_hit.t = INFINITY;
	i = 0;
	while (i < object->mesh->n_polygons)
	{
		fill_polygon_info(i, object, &polygon);
		if (ray_polygon_intersection(ray, &polygon, &hit) == true \
			&& hit.t < closest_hit.t)
			ft_memcpy(&closest_hit, &hit, sizeof(t_hit_record));
		i++;
	}
	if (closest_hit.t == INFINITY)
		return (false);
	else
	{
		ft_memcpy(record, &closest_hit, sizeof(t_hit_record));
		return (true);
	}
}
