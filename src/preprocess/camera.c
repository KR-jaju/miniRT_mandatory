// dummy
// TODO: 카메라 구조체 관련 전처리 작업 함수 작성 (행렬 구하기 등)
/*
world space상에서의 픽셀 좌표 구하기
1. NDC 좌표로 변환 (=[-1,1] 범위로 매핑)
2. 투영 행렬(P) 및 카메라 행렬(V)의 역행렬 적용하기
3. w 성분을 1로 만들어주기 위해 전체 성분 w값으로 나누기
	(선형변환의 성질에 의해 이 나눗셈 연산을 이때 해도 상관없음)

구해야하는 이미지 플레인 모서리 좌표
(0, 0), (WIDTH, 0), (0, HEIGHT), (WIDTH, HEIGHT)
*/
void camera_fill_corners_world_pos(t_camera *cam, t_image *img)
{
	const t_mat4	pv_inverse = mat4_inverse(mat4_mulmm(\
			projection_matrix(cam->fov, img->width / img->height, NEAR, FAR), \
			view_matrix(cam->right, cam->up, cam->forward, cam->position)));
	t_vec4			corners[4];
	t_vec3			ndc;
	int				i;

	corners[0] = vec4(0, 0, 0, 1);
	corners[1] = vec4(img->width, 0, 0, 1);
	corners[2] = vec4(0, img->height, 0, 1);
	corners[3] = vec4(img->width, img->height, 0, 1);
	i = 0;
	while (i < 4)
	{
		ndc.x = ((corners[i].x + 0.5) / img->width) * 2 - 1;
		ndc.y = 1 - ((corners[i].y + 0.5) / img->height) * 2;
		ndc.z = 0; // -1~1 사이면 아무 값이나 상관없음
		corners[i] = mat4_mulmv(pv_inverse, vec4(ndc.x, ndc.y, ndc.z, 1));
		corners[i] = vec4_mul(corners[i], corners[i].w);
		cam->corners_world_pos[i] = (t_vec3){corners[i].x, corners[i].y, corners[i].z};
		i++;
	}
}

