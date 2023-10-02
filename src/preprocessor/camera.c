#include "scene.h"
#include "settings.h"

t_mat4	view_matrix(t_vec3 right, t_vec3 up, t_vec3 forward, t_vec3 position);
t_mat4	projection_matrix(float fov, float aspect_ratio, float near, float far);

/*
Screen Space -> NDC Space Mapping
: The coordinates on a two-dimensional plane with the origin of the upper left
and the ranges of x and y [0, width), [0, height), respectively,
are mapped to a three-dimensional cube space with the origin of the lower left
and the ranges of x, y, and z [-1, 1].
*/
static t_vec3	screen_to_ndc_space(t_vec3 screen, float depth, \
										int width, int height)
{
	t_vec3	ndc;

	ndc.x = (screen.x / width) * 2 - 1.0f;
	ndc.y = -(screen.y / height) * 2 + 1.0f;
	ndc.z = depth;
	return (ndc);
}

/*
Clip Space -> World Space Mapping
: The inverse matrix of the projection matrix P and the camera matrix V
is applied, and the entire component is divided by w. (=perspective division)
(Because it must be made w=1 so that it can be interpreted as 3D coordinates
in the homogeneous coordinate system.)
*/
static t_vec3	clip_to_world_space(t_vec4 clip, const t_mat4 *pv_inverse)
{
	t_vec4	v4;

	v4 = mat4_mulmv(*pv_inverse, clip);
	vec4_mul(v4, (1 / v4.w));
	return ((t_vec3){v4.x, v4.y, v4.z});
}

/*
Coordinate system mapping process for graphics pipeline is
'world -> view -> clip -> NDC -> screen'
By reversing, the coordinates on the screen space are mapped
to the world space standard.

<Mapping coordinates on screen space to world space>
1. Convert to NDC coordinates (mapped to [-1,1] range)
2. Convert to clip space coordinates (reflect depth on all components)
3. Convert to world space coordinates
(apply inverse matrix of projection matrix (P) and camera matrix (V))

At this time, since it is a mapping from a two-dimensional plane
to a three-dimensional space, an arbitrary depth must be set.
For convenience, ensure that the coordinates of the points obtained
are located on the near plane.
(ndc.z = -1, clip.w = NEAR, view.z = NEAR)
*/
static t_vec3	pixel_to_world_space(int pixel_x, int pixel_y, \
										const t_mat4 *pv_inverse)
{
	t_vec3		screen;
	t_vec3		ndc;
	t_vec4		clip;
	t_vec3		world;

	screen = (t_vec3){pixel_x + 0.5, pixel_y + 0.5, 0};
	ndc = screen_to_ndc_space(screen, -1, IMAGE_WIDTH, IMAGE_HEIGHT);
	clip = vec4_mul((t_vec4){ndc.x, ndc.y, ndc.z, 1}, NEAR);
	world = clip_to_world_space(clip, pv_inverse);
	return (world);
}

/*
In ray tracing, the parameters of the camera are eventually used to obtain
the camera ray direction vector.
The camera ray direction vector is obtained by subtracting
the camera coordinates from the world space coordinates of the pixel
that want to obtain the current color, and it is inefficient to obtain the
inverse matrix of PV for each pixel to obtain the world space coordinates,
so for more efficient execution, the four world space coordinates
of the corner of the image plane are obtained in advance
and used later by interpolating them.
*/
int	preprocess_camera(t_camera *cam)
{
	const t_mat4	pv = mat4_mulmm(\
			projection_matrix(cam->fov, (float)IMAGE_WIDTH / IMAGE_HEIGHT, \
																NEAR, FAR), \
			view_matrix(cam->right, cam->up, cam->forward, cam->position));
	const t_mat4	pv_inverse = mat4_inverse(pv);
	const int		corners[4][2] = {{0, 0}, \
									{IMAGE_WIDTH, 0}, \
									{0, IMAGE_HEIGHT}, \
									{IMAGE_WIDTH, IMAGE_HEIGHT}};
	int				i;

	i = 0;
	while (i < 4)
	{
		cam->corners_world_pos[i] = \
			pixel_to_world_space(corners[i][0], corners[i][1], &pv_inverse);
		i++;
	}
	return (0);
}
