/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:38 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:39 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libds.h"

bool	stack_is_empty(t_stack *this)
{
	return (this->count == 0);
}

bool	stack_is_full(t_stack *this)
{
	return (this->count == this->capacity);
}
