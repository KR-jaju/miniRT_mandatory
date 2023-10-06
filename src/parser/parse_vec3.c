/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_vec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:59 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:05:00 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_internal.h"
#include "libmath.h"
#include <stdlib.h>

t_vec3	parse_vec3(const char **str_ref)
{
	t_vec3	v;

	v.x = parse_float(str_ref);
	if (*(*str_ref)++ != ',')
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	v.y = parse_float(str_ref);
	if (*(*str_ref)++ != ',')
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	v.z = parse_float(str_ref);
	return (v);
}
