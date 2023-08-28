/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:40:42 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/03/09 04:01:48 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*occur;

	if ((char) c == '\0')
		return ((char *)(s + ft_strlen(s)));
	i = 0;
	occur = NULL;
	while (s[i])
	{
		if (s[i] == (char) c)
			occur = ((char *)&s[i]);
		i++;
	}
	return (occur);
}
