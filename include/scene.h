#ifndef SCENE_H
#define SCENE_H

# include "libmath.h"

typedef struct s_polygon {
	t_vec3		vertex[3];
	t_vec3		normal;
}	t_polygon;

typedef struct s_mesh {
	t_polygon	*polygons;
	int			n_polygons;
}	t_mesh;

typedef struct s_object {
	t_mesh		*mesh;
	t_vec3		position;
	t_vec3		rotation;
	float		scale;
	t_vec3		color;
}	t_object;

typedef struct s_camera {
	t_vec3		position;
	t_vec3		rotation;
	t_vec3		right;
	t_vec3		up;
	t_vec3		forward;
	float		fov;
}	t_camera;

typedef struct s_light {
	t_vec3		position;
	t_vec3		color;
}	t_light;

typedef struct s_scene {
	t_object	*objects;
	t_mesh		*meshs;
	t_camera	camera;
	t_light		light;
	t_vec3		ambient_light;
}	t_scene;

#endif
