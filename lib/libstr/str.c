/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaju <jaju@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 20:18:01 by jaju              #+#    #+#             */
/*   Updated: 2023/08/29 14:13:36 by jaju             ###   ########.fr       */
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

//문자열의 길이를 리턴
int	str_length(char const *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

//str의 [start, end)만큼을 복사, str[end]는 포함하지 않음
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
			return (copy);//or exit(1);
		copy[i - start] = str[i];
		i++;
	}
	return (copy);
}

//str안에 c가 있으면 1, 없으면 0
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

//strtok과 같음
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

//str에 있는 모든 replaced를 with로 치환한 문자열을 생성
char	*str_replace(char const *str, char const *replaced, char *with)
{
	int const	size = 1
		+ str_length(str) / str_length(replaced) * str_length(with)
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

//a와 b가 같다면 1, 다르다면 0
int	str_equals(char const *a, char const *b)
{
	int	i;

	i = 0;
	while (a[i] != '\0' && b[i] != '\0' && a[i] == b[i])
		i++;
	return (a[i] == b[i]);
}

//a와 b를 붙인 새로운 문자열을 생성
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

//str에서 c가 몇 번째 인덱스에 있는지 리턴, 없으면 -1
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

//str을 복제하는 함수
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
