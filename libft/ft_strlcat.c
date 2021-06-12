/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 17:02:51 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/04/14 17:05:15 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst,
			const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_size;
	size_t	src_size;

	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	if (dstsize <= dst_size)
		return (dstsize + src_size);
	i = 0;
	while (i < dstsize - dst_size - 1 && src[i])
	{
		dst[i + dst_size] = src[i];
		++i;
	}
	dst[i + dst_size] = '\0';
	return (dst_size + src_size);
}
