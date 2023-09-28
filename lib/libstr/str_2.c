/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:12:56 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/09/28 15:13:29 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libstr.h"
#include <stdlib.h>

char	*str_replace(char const *str, char const *replaced, char *with)
{
	int const	size = 1
		+ str_length(str) / str_length(replaced) * swtr_length(with)
		+ str_length(str) % str_length(replaced);
	char*const	new = allocate(size * sizeof(char));
	int			i;
	int			j;

	i = 0;
	while (str[0] != '\0')
	{
		j = 0;
		while (str[j] != '\0' && replaced[j] != '\0' && replaced[j] == str[j])
			j++;
		if (replaced[j] == '\0')
		{
			str += j;
			j = 0;
			while (with[j] != '\0')
				new[i++] = with[j++];
			continue ;
		}
		new[i++] = (str++)[0];
	}
	return (new);
}

int	str_equals(char const *a, char const *b)
{
	int	i;

	i = 0;
	while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
		i++;
	return (a[i] == b[i]);
}

char	*str_join(char const *a, char const *b)
{
	int const	length = str_length(a) + str_length(b);
	char*const	new = allocate(length + 1);
	char		*ptr;

	ptr = new;
	while (*a != '\0')
		*(ptr++) = *(a++);
	while (*b != '\0')
		*(ptr++) = *(b++);
	return (new);
}

int	str_indexof(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*str_clone(char const *str)
{
	char	*new;
	char	*ptr;

	if (str == (void *)0)
		return ((void *)0);
	new = allocate((str_length(str) + 1) * sizeof(char));
	ptr = new;
	while (*str != '\0')
		*(ptr++) = *(str++);
	return (new);
}
