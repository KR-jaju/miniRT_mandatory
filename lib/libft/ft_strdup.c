/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:40:42 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/03/09 04:01:34 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dst;
	size_t	srcsize;
	int		i;

	srcsize = 0;
	while (s1[srcsize])
		srcsize++;
	dst = malloc(srcsize + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (*s1)
		dst[i++] = *s1++;
	dst[i] = '\0';
	return (dst);
}
