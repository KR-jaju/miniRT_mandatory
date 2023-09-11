#include "render.h"

/*
교차점 색상 계산:
최종 색상 = 환경광(ambient) + 난반사(diffuse) + 하이라이트(specular)
레이, 폴리곤의 노말벡터를 통해 계산한다.
*/
t_vec3	calculate_intersection_color(t_hit_record *hit, t_scene *scene);
