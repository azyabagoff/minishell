/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 20:21:23 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/18 21:03:51 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_strrev(char *str)
{
	size_t	len;
	size_t	i;
	char	tmp;

	len = ft_strlen(str);
	i = 0;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[len - i - 1];
		str[len - i - 1] = tmp;
		++i;
	}
}

static int	get_len_int(int n)
{
	int		len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		++len;
		n /= 10;
	}
	return (len);
}

static char	*ft_min_ll(char **str)
{
	*str = ft_strdup("-9223372036854775808");
	return (*str);
}

static void	put_in_arr(unsigned long long *cp, char **str, size_t *len)
{
	while ((*cp) != 0)
	{
		(*str)[(*len)++] = (*cp) % 10 + '0';
		(*cp) /= 10;
	}
}

char	*ft_lltoa(long long n)
{
	char				*str;
	int					is_neg;
	size_t				len;
	unsigned long long	cp;

	str = NULL;
	if (n == (long long)(-9223372036854775807 - 1))
		return (ft_min_ll(&str));
	cp = (unsigned long long)
		ft_ternar_ll((n < 0), (long long)(-n), (long long)n);
	is_neg = (n < 0);
	str = ft_calloc(get_len_int(n) + is_neg + 1, sizeof(*str));
	if (!str)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	len = 0;
	put_in_arr(&cp, &str, &len);
	if (is_neg)
		str[len++] = '-';
	ft_strrev(str);
	return (str);
}
