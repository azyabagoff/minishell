/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 12:24:53 by sesnowbi          #+#    #+#             */
/*   Updated: 2020/11/08 16:15:44 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*str1;

	if (!len || dst == src)
		return (dst);
	i = 0;
	str1 = (unsigned char *)dst;
	if (dst > src)
		while (len--)
			*(char *)(str1 + len) = *(char *)(src + len);
	else
	{
		while (i < len)
		{
			*(char *)(str1 + i) = *(char *)(src + i);
			++i;
		}
	}
	return (dst);
}
