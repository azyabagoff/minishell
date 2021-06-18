/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 18:34:23 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/18 20:20:10 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_space(char c)
{
	if (c == ' ' || c == '\f' || c == '\n'
		|| c == '\r' || c == '\t' || c == '\v')
		return (1);
	else
		return (0);
}

static long long	ret_val_ll(unsigned long long res, int is_neg)
{
	if (is_neg)
		return (ft_ternar_ll((res > (unsigned long long)9223372036854775807
					&& res != (unsigned long long)
					((unsigned long long)9223372036854775807 + 1)), 0, -res));
	return (ft_ternar_ll((
				res > (unsigned long long)9223372036854775807), -1, res));
}

long long	ft_atoll(const char *str)
{
	unsigned long long	res;
	int					is_neg;

	is_neg = 0;
	res = 0;
	while (ft_is_space(*str) == 1)
		++str;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			is_neg = (is_neg + 1) % 2;
		++str;
	}
	while (*str == '0')
		++str;
	while (res <= 9223372036854775807 && ft_isdigit(*str))
	{
		res *= 10;
		res += *str - '0';
		++str;
	}
	return (ret_val_ll(res, is_neg));
}
