/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:47 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:48 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser_internal.h"

static
float	parse_sign(const char **str_ref)
{
	if (**str_ref == '-')
		return ((*str_ref)++, -1);
	if (**str_ref == '+')
		return ((*str_ref)++, 1);
	return (1);
}

static
float	parse_integer_part(const char **str_ref)
{
	float	integer_part;

	if (!('0' <= **str_ref && **str_ref <= '9'))
		handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	integer_part = 0;
	while (ft_isdigit(**str_ref))
	{
		integer_part *= 10;
		integer_part += **str_ref - '0';
		(*str_ref)++;
	}
	return (integer_part);
}

static
float	parse_decimal_part(const char **str_ref)
{
	float	decimal_part;
	float	place;

	(*str_ref)++;
	decimal_part = 0;
	place = 0.1f;
	while (ft_isdigit(**str_ref))
	{
		decimal_part += place * (**str_ref - '0');
		place *= 0.1f;
		(*str_ref)++;
	}
	return (decimal_part);
}

float	parse_float(const char **str_ref)
{
	const float	sign = parse_sign(str_ref);
	const float	integer_part = parse_integer_part(str_ref);
	float		decimal_part;

	if (**str_ref == '.')
	{
		if (ft_isdigit(*(*str_ref + 1)))
		{
			decimal_part = parse_decimal_part(str_ref);
			return (sign * (integer_part + decimal_part));
		}
		else
			handle_parse_error(ERROR_INVALID_LINE_FORMAT);
	}
	return (sign * integer_part);
}
