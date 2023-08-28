/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_info.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:40:42 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/03/09 04:02:39 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_internal.h"

static int	get_flags(const char **format)
{
	int	flag;

	flag = 0;
	while (fmt_strchr(FLAGS, **format) != FAIL)
	{
		flag |= 0b1 << fmt_strchr(FLAGS, **format);
		(*format)++;
	}
	if (flag & FLAG_LEFT)
		flag &= ~FLAG_ZERO;
	if (flag & FLAG_PLUS)
		flag &= ~FLAG_SPACE;
	return (flag);
}

void	parse_format_info(const char **format, t_finfo f_info)
{	
	(*format)++;
	{
		f_info->flag = get_flags(format);
		if (f_info->flag & FLAG_ZERO)
			f_info->pad = '0';
		else
			f_info->pad = ' ';
	}
	f_info->width = fmt_atoi(format);
	if (**format == '.')
	{
		f_info->flag |= FLAG_PRECISION;
		f_info->flag &= ~FLAG_ZERO;
		f_info->pad = ' ';
		(*format)++;
		f_info->prsc = fmt_atoi(format);
	}
	else
		f_info->prsc = 1;
	f_info->type = fmt_strchr(TYPES, **format);
	(*format)++;
}
