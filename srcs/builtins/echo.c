/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 19:55:13 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/05 21:29:27 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	remember_echo_n(t_mini *mini, char *str, int *flag)
{
	if (*flag == 1)
	{
		mini->echo_n = ft_strjoin_mini(mini->echo_n, " ");
		if (!mini->echo_n)
			exit_err_malloc_mini(mini, NULL, NULL);
		mini->echo_n = ft_strjoin_mini(mini->echo_n, str);
		if (!mini->echo_n)
			exit_err_malloc_mini(mini, NULL, NULL);
	}
}

static void	echo_cases(t_mini *mini, char *str, int *flag, int i)
{
	if (i == 1)
	{
		if (!ft_strcmp(str, "-n"))
		{
			mini->fl_echo_n = 1;
			*flag = 1;
		}
		else
			ft_putstr_fd(str, 1);
	}
	else if (i == 2 && *flag)
	{
		ft_putstr_fd(str, 1);
		mini->echo_n = ft_strjoin_mini(mini->echo_n, str);
		if (!mini->echo_n)
			exit_err_malloc_mini(mini, NULL, NULL);
	}
	else
	{
		remember_echo_n(mini, str, flag);
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(str, 1);
	}
}

int	ft_echo(t_mini *mini, char **args)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (args[++i])
		echo_cases(mini, args[i], &flag, i);
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
