/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:40:54 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/04/14 17:40:49 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*res;
	size_t		res_len;

	if (!s1)
		return (NULL);
	if (!s2)
		return ((char *)s1);
	res_len = ft_strlen(s1) + ft_strlen(s2);
	res = malloc(sizeof(char) * (res_len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, res_len + 1);
	ft_strlcat(res, s2, res_len + 1);
	return (res);
}
