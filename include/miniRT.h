#ifndef MINIRT_H
#define MINIRT_H

# include "geometry.h"

typedef struct s_face {
	int			idx_vertex[3];
	t_vector3	normal;
}	t_face;

typedef struct s_mesh {
	t_vector3	*vertices;
	t_face		*faces;
	int			n_vertices;
	int			n_faces;
}	t_mesh;

typedef struct s_object {
	t_mesh		*mesh;
	t_vector3	position;
	t_vector3	rotation;
	float		scale;
	t_vector3	color;
}	t_object;

typedef struct s_camera {
	t_vector3	position;
	t_vector3	rotation;
	t_vector3	right;
	t_vector3	up;
	t_vector3	forward;
	float		fov;
}	t_camera;

typedef struct s_light {
	t_vector3	position;
	t_vector3	color;
}	t_light;

typedef struct s_scene {
	t_object	*objects;
	t_mesh		*meshs;
	t_camera	camera;
	t_light		light;
	t_vector3	ambient_light;
}	t_scene;

#endif
