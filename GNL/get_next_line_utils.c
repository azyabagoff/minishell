/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:44:05 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/04/14 19:56:44 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft__strlen(const char *s)
{
	int	size;

	if (!s)
		return (0);
	size = 0;
	while (s[size])
		++size;
	return (size);
}

char	*ft__strjoin(char *s1, char *s2)
{
	char		*new;
	char		*tmp;
	int			i;
	int			res_len;

	if (!s1 && !s2)
		return (NULL);
	res_len = (ft__strlen(s1) + ft__strlen(s2) + 1) * sizeof(char);
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

static char	*ft_free_for_cut(char *str, char *ret)
{
	if (str)
		free(str);
	return ((char *)ret);
}

char	*ft_cut_after_endl(char *str)
{
	char	*res;
	int		i;

	i = 0;
	while (str[i] != '\n' && str[i])
		++i;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (ft_free_for_cut(str, NULL));
	i = 0;
	while (str[i] != '\n' && str[i])
	{
		res[i] = str[i];
		++i;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_cut_before_endl(char *str)
{
	char	*res;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		++i;
	if (str[i++] == '\0')
		return (ft_free_for_cut(str, NULL));
	j = 0;
	while (str[i + j])
		++j;
	res = (char *)malloc(sizeof(char) * (j + 1));
	if (!res)
		return (ft_free_for_cut(str, NULL));
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	free(str);
	return (res);
}
