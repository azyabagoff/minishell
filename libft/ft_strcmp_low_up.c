/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_low_up.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 14:13:43 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/08/02 14:26:11 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp_low_left(const char *s1, const char *s2)
{
	int		len1;
	int		len2;
	char	*cmp_str;
	int		ret;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	cmp_str = ft_str_tolower((char *)s1);
	ret = ft_strncmp(cmp_str, s2, ft_tern_i((len1 > len2), len1, len2));
	free(cmp_str);
	return (ret);
}

int	ft_strcmp_up_left(const char *s1, const char *s2)
{
	int		len1;
	int		len2;
	char	*cmp_str;
	int		ret;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	cmp_str = ft_str_toupper((char *)s1);
	ret = ft_strncmp(cmp_str, s2, ft_tern_i((len1 > len2), len1, len2));
	free(cmp_str);
	return (ret);
}
