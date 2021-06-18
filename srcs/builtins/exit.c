/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:38:43 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/18 21:12:09 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	cast_status(long long status)
{
	if (status < 0)
		return (256 - (status % 256));
	else if (status > 255)
		return (status % 256);
	return (status);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (i == 0)
		{
			if (!ft_isdigit(str[i]) && str[i] != '-' && str[i] != '+')
				return (0);
		}
		else
		{
			if (!ft_isdigit(str[i]))
				return (0);
		}
		++i;
	}
	return (1);
}

static int	belongs_long_long(char *str)
{
	char	*lltoa;

	lltoa = NULL;
	lltoa = ft_lltoa(ft_atoll(str));
	if (ft_strcmp(str, lltoa))
	{
		free(lltoa);
		lltoa = NULL;
		return (0);
	}
	free(lltoa);
	lltoa = NULL;
	return (1);
}

int	ft_exit(char ***envs, char ***args)
{
	ft_putstr_fd("exit\n", 1);
	if (args && (*args)[1])
	{
		if (!is_numeric((*args)[1]) || !belongs_long_long((*args)[1]))
		{
			ft_putstr_fd("minishell: exit: ", 1);
			ft_putstr_fd((*args)[1], 1);
			ft_putstr_fd(": numeric argument required\n", 1);
			g_status = 255;
		}
		else
		{
			if ((*args)[2])
			{
				ft_putstr_fd("minishell: exit: ", 1);
				ft_putstr_fd(": too many arguments\n", 1);
				return (1);
			}
			g_status = ft_atoll((*args)[1]);
		}
	}
	free_2dim_arr(*envs);
	free_2dim_arr(*args);
	exit(cast_status(g_status));
	return (0);
}
