/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:11 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:12 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_api.h"

int	shutdown_program(void *data);

int	keypress_hook(int keycode, void *data)
{
	if (keycode == KEY_ESC)
		shutdown_program(data);
	return (0);
}
