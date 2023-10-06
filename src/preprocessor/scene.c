/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:36 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:37 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "scene.h"

int		preprocess_object(t_object *obj);
int		preprocess_camera(t_camera *cam);

int	preprocess_scene(t_scene *scene)
{
	int	i;

	i = 0;
	while (i < scene->n_objects)
	{
		if (preprocess_object(&scene->objects[i]) == -1)
			return (-1);
		i++;
	}
	preprocess_camera(&scene->camera);
	return (0);
}
