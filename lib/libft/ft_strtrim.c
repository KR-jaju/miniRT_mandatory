/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:40:42 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/03/09 04:01:50 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(const char c, const char *set)
{
	while (*set)
	{
		if (c == *set++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	char	*start;
	char	*end;

	if (!set)
		return (ft_strdup(s1));
	start = (char *)s1;
	end = (char *)(s1 + ft_strlen(s1) - 1);
	while (is_in_set(*start, set))
		start++;
	if (!*start)
		return (ft_strdup(""));
	while (is_in_set(*end, set))
		end--;
	dst = malloc(sizeof(char) * (end - start + 1) + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, start, (end - start + 1) + 1);
	return (dst);
}
