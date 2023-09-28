#ifndef SETTINGS_H
# define SETTINGS_H

/* display */
# define WINDOW_TITLE 				"miniRT"
# define IMAGE_WIDTH				800
# define IMAGE_HEIGHT				600
# define IMAGE_PUT_INTERVAL_PERCENT	5

/* camera */
# define NEAR	0.3 // 사실 아무 값이나 상관없음
# define FAR	1000 // 사실 아무 값이나 상관없음

/* render option */
# define SMOOTH_SHADING		1 // Shading mode (Flat or Smooth)
# define RESOLUTION			1 // 폴리곤 개수 비율 (해상도)
# define PLANE_SIDE_LENGTH	1 // length of one side of a plane

/* material */
# define REFLECTIVITY		0.3
# define K_DIFFUSE			0.3 // recommended: K_DIFFUSE + K_SPECULAR <= 1
# define K_SPECULAR			0.7 // recommended: K_DIFFUSE + K_SPECULAR <= 1
# define SHININESS			64

#endif
