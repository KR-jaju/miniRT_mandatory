/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:40:42 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/03/09 04:01:14 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*s1_p;
	const unsigned char	*s2_p;

	s1_p = (const unsigned char *)s1;
	s2_p = (const unsigned char *)s2;
	while (n--)
	{
		if (*s1_p != *s2_p)
			return (*s1_p - *s2_p);
		s1_p++;
		s2_p++;
	}
	return (0);
}
