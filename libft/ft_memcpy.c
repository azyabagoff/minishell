/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 19:42:47 by sesnowbi          #+#    #+#             */
/*   Updated: 2020/11/08 16:12:53 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*str1;

	i = 0;
	str1 = (unsigned char *)dst;
	if (!n || dst == src)
		return (dst);
	while (i < n)
	{
		*(char *)(str1 + i) = *(char *)(src + i);
		++i;
	}
	return (dst);
}
