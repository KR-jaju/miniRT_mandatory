
#include "libft.h"
#include "render.h"

// 폴리곤-레이 교차 검사
bool	ray_polygon_intersection(t_ray *ray, t_polygon *polygon, t_hit_record *record);

//TODO: closest_hit 없어도 안 헷갈릴 것 같으면 record 대체하고 불필요한 연산 줄이기
/*
오브젝트 교차 검사:
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
