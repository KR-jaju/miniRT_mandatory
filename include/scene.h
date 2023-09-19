#ifndef SCENE_H
#define SCENE_H

# include "libmath.h"

// default material
# define REFLECTIVITY	0.3
# define K_DIFFUSE		0.3
# define K_SPECULAR		0.7
# define SHININESS		64
// diffuse 상수값 + specular 상수값 <= 1

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

typedef struct s_mesh
{
	t_vec3		*vertices;
	t_vec3		*vertex_normals;
	int			*indices; // 시계 반대 방향(ccw)으로 저장
	int			n_vertices;
	int			n_indices;
	int			n_triangles;
}t_mesh;

// mesh는 다면체의 기본 형태(아무런 변환x)
typedef struct s_object
{
	t_mesh		*mesh;
	t_vec3		*vertices; // 변환 후 버텍스 좌표
	t_vec3		*vertex_normals; // 변환 후 버텍스 노멀
	t_triangle	*triangles;
	t_vec3		position;
	t_vec3		rotation;
	t_vec3		scale;
	t_material	material;
}t_object;

typedef struct s_camera
{
	t_vec3		eye; // 차후 position으로 이름 바꿀 예정
	t_vec3		right;
	t_vec3		up;
	t_vec3		forward;
	float		fov; // 육십분법
}t_camera;

typedef struct s_light
{
	t_vec3		position;
	t_vec3		color;
}t_light;

/*
meshs에는 해당 씬이 담는 다면체의 기본형 메쉬가 들어갈 것임
즉 만약 이 씬에 3가지의 다면체가 존재한다면, 메쉬 배열의 요소 개수는 3개
object 구조체는 이 기본 메쉬를 포인터로 들고있음
*/
typedef struct s_scene
{
	t_mesh		meshs[3];
	t_object	*objects;
	t_camera	camera;
	t_light		light;
	t_vec3		ambient_light;
	int			n_meshs;
	int			n_objects;
}t_scene;

#endif
