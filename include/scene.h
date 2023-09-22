#ifndef SCENE_H
#define SCENE_H

# include "libmath.h"
# include "mesh.h"

typedef struct s_material
{
	t_vec3	color;
	float	reflectivity;
	float	k_diffuse;
	float	k_specular;
	float	shininess;
}t_material;

typedef struct s_triangle
{
	t_vec3		vertices[3];
	t_vec3		vertex_normals[3];
	t_vec3		face_normal;
}t_triangle;

typedef struct s_object
{
	t_mesh		*mesh;
	t_vec3		*vertices;
	t_vec3		*vertex_normals;
	t_triangle	*triangles;
	t_vec3		position;
	t_vec3		rotation;
	t_vec3		scale;
	t_material	material;
}t_object;

typedef struct s_camera
{
	t_vec3		position;
	t_vec3		right;
	t_vec3		up;
	t_vec3		forward;
	float		fov;
	t_vec3		corners_world_pos[4];
}t_camera;

typedef struct s_light
{
	t_vec3		position;
	t_vec3		color;
}t_light;

typedef struct s_scene
{
	t_mesh		meshs[MESH_COUNT];
	t_object	*objects;
	t_camera	camera;
	t_light		light;
	t_vec3		ambient_light;
	int			n_objects;
}t_scene;

#endif
