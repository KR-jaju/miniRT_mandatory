
#include "render.h"

// 폴리곤-레이 교차 검사
bool	intersection_check_polygon(t_polygon *polygon, t_ray ray, t_hit_record *hit_record);

/*
오브젝트 교차 검사:
오브젝트의 모든 폴리곤을 돌며 가장 가까운 hit을 찾는다.
*/
bool	intersection_check_object(t_object *object, t_ray ray, \
									t_hit_record *hit_record)
{
	t_object		*polygon;
	t_hit_record	hit;
	t_hit_record	closest_hit;

	closest_hit.t = INFINITY;
	polygon = &object->mesh->polygons[0];
	while (polygon)
	{
		if (intersection_check_polygon(polygon, ray, &hit) \
			&& hit.t < closest_hit.t)
			ft_memcpy(&closest_hit, &hit, sizeof(t_hit_record));
		polygon++;
	}
	if (closest_hit.t == INFINITY)
		return (false);
	else
		return (true);
}
