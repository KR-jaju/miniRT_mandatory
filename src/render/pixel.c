#include "libft.h"
#include "mlx_api.h"
#include "render.h"
#include "settings.h"

/*
Camera orientation vector
: camera position -> pixel position

Linearly interpolate the world space coordinates of the four points
at the corners of the image plane obtained in the preprocessing work
to get the world space coordinates of the pixel we want to get,
and subtract the coordinates of the camera to get the camera direction vector.
*/
static t_vec3	camera_ray_direction(int x, int y, t_camera *cam, t_image *img)
{
	t_vec3				pixel_world_pos;
	const float			x_percentage = (float)x / img->width;
	const float			y_percentage = (float)y / img->height;
	float				ratio[4];

	ratio[0] = (1.0f - x_percentage) * (1.0f - y_percentage);
	ratio[1] = x_percentage * (1.0f - y_percentage);
	ratio[2] = (1.0f - x_percentage) * y_percentage;
	ratio[3] = x_percentage * y_percentage;
	pixel_world_pos = vec3_interpolate(cam->corners_world_pos, ratio, 4);
	return (vec3_normalize(vec3_sub(pixel_world_pos, cam->position)));
}

/*
Use phong lighting model.

color = Ambient + Diffuse + Specular  
(Adjusting the ratio of diffuse and specular terms according to the material
of the object)
(coefficients of the Diffuse term + coefficients of the Specular = 1)

Parameters for each term
- Ambient: Background color (very simple as it is a local lighting model)
- diffuse: Incident vector of light, Normal vector at intersection
- Specific: Reflection vector of light, View vector

It is divided into Flat shading and Smooth shading
depending on how the normal vector of the intersection is set.
- Using Polygon's normal (face normal) -> Flat shading
- Using normal obtained by interpolating three vertex normal
	that make up the polygon -> Smooth shading
*/
static t_vec3	shading(t_hit_record *hit, const t_scene *scene)
{
	const t_material	*material = hit->material;
	const t_vec3		incident = incident_direction(\
									hit->point, scene->light.position);
	t_vec3				ambient;
	t_vec3				diffuse;
	t_vec3				specular;

	if (SMOOTH_SHADING == 1)
		hit->normal = interpolate_normal(hit->point, hit->triangle);
	else
		hit->normal = hit->triangle->face_normal;
	ambient = vec3_hadamard(scene->ambient_light, material->color);
	diffuse = diffuse_reflection_value(material, scene->light.color, \
										incident, hit->normal);
	specular = specular_reflection_value(material, scene->light.color, \
						reflection_direction(incident, hit->normal), \
						view_direction(scene->camera.position, hit->point));
	return (vec3_add(ambient, \
			vec3_add(vec3_mul(diffuse, (float)1 - material->reflectivity), \
					vec3_mul(specular, (float)material->reflectivity))));
}

/*
1. Create Camera Ray
2. Check intersection with objects in scene, find nearest object  
3.1. If found: Return Shaded color of the intersection
3.2. If not found: Return background color
*/
t_vec3	render_pixel(int x, int y, t_scene *scene, t_image *img)
{
	t_ray			cam_ray;
	t_hit_record	hit;
	t_hit_record	closest_hit;
	int				i;

	closest_hit.t = INFINITY;
	cam_ray.origin = scene->camera.position;
	cam_ray.dir = camera_ray_direction(x, y, &scene->camera, img);
	i = 0;
	while (i < scene->n_objects)
	{
		if (ray_object_intersection(&cam_ray, &scene->objects[i], &hit) == true \
			&& hit.t < closest_hit.t)
			ft_memcpy(&closest_hit, &hit, sizeof(t_hit_record));
		i++;
	}
	if (closest_hit.t == INFINITY)
		return (scene->ambient_light);
	else
		return (shading(&closest_hit, scene));
}
