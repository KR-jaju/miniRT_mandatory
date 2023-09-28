/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:18:01 by jaju              #+#    #+#             */
/*   Updated: 2023/09/28 15:13:30 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"
#include <stdlib.h>

typedef unsigned char	t_byte;// allocate랑 한 세트

static
void	*allocate(int size)
{
	t_byte*const	ptr = malloc(size);
	int				i;

	if (ptr == (void *)0)
		exit(1);
	i = 0;
	while (i < size)
	{
		ptr[i] = (t_byte)0;
		i++;
	}
	return (ptr);
}

int	str_length(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*str_substr(char const *str, int start, int end)
{
	int const	length = str_length(str);
	char		*copy;
	int			i;

	if (end <= start)
		return ((void *)0);
	copy = allocate((end - start + 1) * sizeof(char));
	i = start;
	while (i < end)
	{
		if (i >= length)
			return (copy);
		copy[i - start] = str[i];
		i++;
	}
	return (copy);
}

int	str_includes(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*str_tokenize(char *str, char const *delim)
{
	static char	*saved;
	char		*tmp;

	if (str != (void *)0)
		saved = str;
	if (saved == (void *)0)
		return ((void *)0);
	while (str_includes(delim, *saved))
		saved++;
	tmp = saved;
	while (*saved != '\0' && !str_includes (delim, *saved))
		saved++;
	if (*saved == '\0')
		saved = (void *)0;
	else
		*(saved++) = '\0';
	return (tmp);
}
