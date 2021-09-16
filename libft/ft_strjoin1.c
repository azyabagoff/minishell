/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 20:40:16 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/06 14:09:21 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	char		*new;
	char		*tmp;
	int			i;
	int			res_len;

	if (!s1 && !s2)
		return (NULL);
	res_len = (ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char);
	new = (char *)malloc(res_len);
	if (!new)
		return (NULL);
	i = 0;
	while (i < res_len)
		*(new + i++) = (char)0;
	tmp = new;
	i = 0;
	while (s1 && s1[i] != '\0')
		*(new++) = s1[i++];
	if (s1)
		free(s1);
	while (s2 && *s2 != '\0')
		*(new++) = *(s2++);
	return (tmp);
}
