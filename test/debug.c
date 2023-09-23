#include <stdio.h>
#include "libmath.h"
#include "scene.h"

void	print_vec3(t_vec3 v)
{
	printf("x:%f y:%f z:%f\n", v.x, v.y, v.z);
}

void	print_vec4(t_vec4 v)
{
	printf("x:%f y:%f z:%f w:%f\n", v.x, v.y, v.z, v.w);
}

void	print_mat4(t_mat4 m)
{
	int		i;
	int		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			printf("%f ", m.e[j][i]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("------------------\n");
}

int	radian_to_degree(float r)
{
	return (r / M_PI * 180);
}

void	print_scene(t_scene *scene)
{
	printf("\nobject[0]: ");
	printf("\n\tposition=");
	print_vec3(scene->objects[0].position);
	printf("\trotation=");
	print_vec3(scene->objects[0].rotation);
	printf("\tscale=");
	print_vec3(scene->objects[0].scale);
	printf("\tcolor=");
	print_vec3(scene->objects[0].material.color);
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