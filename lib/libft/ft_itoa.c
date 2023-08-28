/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeonhkim <yeonhkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:40:42 by yeonhkim          #+#    #+#             */
/*   Updated: 2023/03/09 04:02:15 by yeonhkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	get_int_length(int n)
{
	size_t	len;

	len = 0;
	if (n <= 0)
		len++;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*dst;
	char	*cur;
	size_t	len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	len = get_int_length(n);
	dst = malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	ft_bzero(dst, len + 1);
	if (n < 0)
	{
		*dst = '-';
		n = -n;
	}
	cur = dst + len - 1;
	while (n)
	{
		*cur-- = (n % 10) + '0';
		n /= 10;
	}
	return (dst);
}
