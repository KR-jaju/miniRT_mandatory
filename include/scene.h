#ifndef SCENE_H
#define SCENE_H

# include "libmath.h"

typedef struct s_mesh
{
	t_vec3		*vertices;
	t_vec3		*normals;
	int			*indices; // 시계 반대 방향(ccw)으로 저장
	int			n_vertices;
	int			n_indices;
	int			n_polygons;
}t_mesh;

// mesh는 다면체의 기본 형태(아무런 변환x)
typedef struct s_object
{
	t_mesh		*mesh;
	t_vec3		*vertices; // 변환 후 버텍스 좌표
	t_vec3		*normals; // 변환 후 버텍스 노멀
	t_vec3		position;
	t_vec3		rotation;
	t_vec3		scale;
	t_vec3		color;
}t_object;

typedef struct s_camera
{
	t_vec3		position;
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
	t_mesh		mesh[3];
	t_object	*objects;
	t_camera	camera;
	t_light		light;
	t_vec3		ambient_light;
	int			n_meshs;
	int			n_objects;
}t_scene;

#endif
