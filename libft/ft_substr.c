/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 13:52:39 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/04/14 17:46:33 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (s_len <= start || s_len == 0 || len == 0)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && *(char *)(s + start + i))
	{
		str[i] = *(char *)(s + start + i);
		++i;
	}
	str[i] = '\0';
	return (str);
}
