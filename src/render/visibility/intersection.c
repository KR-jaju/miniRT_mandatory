/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:18 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:19 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "render.h"
#include "settings.h"

static bool	is_point_in_triangle(t_vec3 p, t_vec3 *tp)
{
	const t_vec3	cross_abap = vec3_cross(vec3_sub(tp[1], tp[0]), \
											vec3_sub(p, tp[0]));
	const t_vec3	cross_bcbp = vec3_cross(vec3_sub(tp[2], tp[1]), \
											vec3_sub(p, tp[1]));
	const t_vec3	cross_cacp = vec3_cross(vec3_sub(tp[0], tp[2]), \
											vec3_sub(p, tp[2]));

	return (vec3_dot(cross_abap, cross_bcbp) >= 0 \
			&& vec3_dot(cross_abap, cross_cacp) >= 0 \
			&& vec3_dot(cross_bcbp, cross_cacp) >= 0);
}

/*
ray-triangle intersect check:
1. Check if the plane of the triangle intersects with the ray
2. If so, make sure that the intersection is inside the triangle

plane: (p-p0) * n = 0
ray: l0 + l * t = p
-> t = (p0 - l0) * n / (n * l)

False when n and l are in the same direction (n * l > 0), 
i.e., when the ray intersects the back of the plane.

False when n and l are parallel (n * l = 0), 
that is, when the plane and the straight line are perpendicular
*/
bool	ray_triangle_intersection(t_ray *ray, t_triangle *tri, \
									t_hit_record *record)
{
	const float	dot_nl = vec3_dot(ray->dir, tri->face_normal);
	float		t;
	t_vec3		point;

	if (-EPSILON < dot_nl)
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
ray-object intersect check:
Trying intersect check ray and all triangles of object and find the closest hit.
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
