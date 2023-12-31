/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:04:39 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/10/06 14:04:40 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "parser_internal.h"
#include "console.h"

int	parser_line_count(int mode)
{
	static int	nth = 1;

	if (mode == COUNT_UP)
		nth++;
	else if (mode == FETCH_COUNT)
		return (nth);
	return (0);
}

void	handle_parse_error(int errcode)
{
	const char	*errmsg[] = {\
		[ERROR_FILEOPEN] = MSG_ERROR_FILEOPEN, \
		[ERROR_INVALID_LINE_FORMAT] = MSG_ERROR_INVALID_LINE_FORMAT, \
		[ERROR_DUPLIATE_DECLARED] = MSG_ERROR_DUPLIATE_DECLARED, \
		[ERROR_MANDATORY_NOT_EXIST] = MSG_ERROR_MANDATORY_NOT_EXIST,
	};

	printf(ANSI_RED);
	if (errcode == ERROR_FILEOPEN || errcode == ERROR_MANDATORY_NOT_EXIST)
		printf("Parse Error: ");
	else
		printf("Parse Error in line %d: ", parser_line_count(FETCH_COUNT));
	printf("%s\n", errmsg[errcode]);
	printf(ANSI_RESET);
	exit(1);
}
