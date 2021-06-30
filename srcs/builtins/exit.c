/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:38:43 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/30 21:38:04 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	cast_status(long long status)
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

int	ft_exit(t_mini *mini)
{
	ft_putstr_fd("exit\n", 1);
	if (mini->els->args && mini->els->args[1])
	{
		if (!is_numeric(mini->els->args[1])
			|| !belongs_long_long(mini->els->args[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(mini->els->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			mini->status = 255;
		}
		else
		{
			if (mini->els->args[2])
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(": too many arguments\n", 2);
				return (1);
			}
			mini->status = ft_atoll(mini->els->args[1]);
		}
	}
	free_mini_strct(mini, 1);
	exit(cast_status(mini->status));
}
