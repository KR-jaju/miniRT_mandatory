/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:35 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:36 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libds.h"

bool	queue_is_empty(t_queue *this)
{
	return (this->count == 0);
}

bool	queue_is_full(t_queue *this)
{
	return (this->count == this->capacity);
}
