/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:01:04 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/04/14 17:45:29 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	size_t	s1_len;

	str = NULL;
	if (!s1)
		return (NULL);
	if (!set)
	{
		str = ft_strjoin((const char *)str, s1);
		if (!str)
			return (NULL);
		return (str);
	}
	while (*s1 && ft_strchr(set, *s1))
		++s1;
	s1_len = ft_strlen(s1);
	while (s1_len && ft_strchr(set, s1[s1_len]))
		--s1_len;
	str = ft_substr((char *)s1, 0, s1_len + 1);
	if (!str)
		return (NULL);
	return (str);
}
