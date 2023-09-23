#include "debug.h"

void	print_object(t_object *object, int nth)
{
	printf("\nobject[%d]: ", nth);
	printf("\n\tposition=");
	print_vec3(object->position);
	printf("\trotation=");
	print_vec3(object->rotation);
	printf("\tscale=");
	print_vec3(object->scale);
	printf("\tcolor=");
	print_vec3(object->material.color);
}

void	print_scene(t_scene *scene)
{
	int	i;

	i = -1;
	while (++i < scene->n_objects)
		print_object(&scene->objects[i], i);
	printf("\ncamera: ");
	printf("\n\tposition=");
	print_vec3(scene->camera.position);
	printf("\tforward=");
	print_vec3(scene->camera.forward);
	printf("\tfov=%f", scene->camera.fov);
	printf("\nlight: ");
	printf("\n\tcolor=");
	print_vec3(scene->light.color);
	printf("\n\tposition=");
	print_vec3(scene->light.position);
	printf("\nambient_light: \n\t");
	print_vec3(scene->ambient_light);
}
