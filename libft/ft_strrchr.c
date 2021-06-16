/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 18:28:34 by sesnowbi          #+#    #+#             */
/*   Updated: 2020/11/07 18:32:59 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	s_len;

	s_len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)(s + s_len));
	while (s_len--)
	{
		if (s[s_len] == (char)c)
			return ((char *)(s + s_len));
	}
	return (NULL);
}
