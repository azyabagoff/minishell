/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_lower_upper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 14:01:12 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/08/02 14:08:08 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_str_tolower(char *str)
{
	char	*res_str;
	int		i;

	if (!str)
		return (NULL);
	res_str = ft_strdup(str);
	if (!res_str)
		return (NULL);
	i = 0;
	while (res_str[i])
	{
		res_str[i] = ft_tolower(str[i]);
		++i;
	}
	return (res_str);
}

char	*ft_str_toupper(char *str)
{
	char	*res_str;
	int		i;

	if (!str)
		return (NULL);
	res_str = ft_strdup(str);
	if (!res_str)
		return (NULL);
	i = 0;
	while (res_str[i])
	{
		res_str[i] = ft_toupper(str[i]);
		++i;
	}
	return (res_str);
}
