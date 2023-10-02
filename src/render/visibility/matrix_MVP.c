#include "libft.h"
#include "libmath.h"
#include "render.h"

/*
Local Space -> World Space Mapping
: Compose three matrices, T, R, and S.
*/
t_mat4	model_matrix(t_vec3 pos, t_vec3 rot, t_vec3 scale)
{
	t_mat4	t;
	t_mat4	r;
	t_mat4	s;

	t = translate_matrix(pos);
	r = rotate_matrix(rot);
	s = scale_matrix(scale);
	return (mat4_mulmm(t, mat4_mulmm(r, s)));
}

/*
World Space -> View Space Mapping

: The view space is the space formed by the camera's three direction vectors,
You can use the camera direction vector that you already know as the row vector.
Since the three axes are mapped between orthogonal Euclidean spaces, 
we can simply think of it as a transition of the basis vector.
(right - x-axis, up - y-axis, forward - z-axis)

In order to map to the view space, 
first, the center is moved to the camera (movement conversion), 
and then rotation conversion is performed.
View Matrix = R * T
*/
t_mat4	view_matrix(t_vec3 right, t_vec3 up, t_vec3 forward, t_vec3 position)
{
	t_mat4	r;
	t_mat4	t;

	r.col[0] = (t_vec4){right.x, up.x, forward.x, 0};
	r.col[1] = (t_vec4){right.y, up.y, forward.y, 0};
	r.col[2] = (t_vec4){right.z, up.z, forward.z, 0};
	r.col[3] = (t_vec4){0, 0, 0, 1};
	t = translate_matrix(vec3_mul(position, -1));
	return (mat4_mulmm(r, t));
}

/*
View Space -> Clip Space Mapping
: In order to give a sense of perspective, 
it is mapped to a Proustam made by camera parameters. (FOV, near, far, ratio...)
*/
t_mat4	projection_matrix(float fov, float aspect_ratio, float near, float far)
{
	const float	fov_radian = M_PI / 180 * fov;
	const float	d = 1.0f / tanf(fov_radian * 0.5f);
	const float	values[16] = {
		d, 0, 0, 0,
		0, d * aspect_ratio, 0, 0,
		0, 0, -(near + far) / (near - far), 1,
		0, 0, 2 * near * far / (near - far), 0
	};

	return (mat4_by_values(values));
}
