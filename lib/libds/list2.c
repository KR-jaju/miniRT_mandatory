/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:05:29 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:30 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libds.h"

void	*list_collect(t_list *this, uint32_t *len)
{
	uint8_t*const	new = malloc(this->count * this->type_size);

	if (new == (void *)0)
		return ((void *)0);
	if (len != (void *)0)
		*len = this->count;
	ft_memmove(new, this->data, this->count * this->type_size);
	return (new);
}

void	list_free(t_list *this)
{
	free(this->data);
	this->capacity = 0;
	this->count = 0;
	this->type_size = 0;
}
