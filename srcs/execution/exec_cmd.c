/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:14:37 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/29 22:02:51 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_chosen_cmd(t_mini *mini)
{
	if (!ft_strcmp(mini->els->args[0], "echo"))
		exit_no_err(mini, ft_echo(mini->els->args));
	else if (!ft_strcmp(mini->els->args[0], "cd"))
		exit_no_err(mini, ft_cd(mini));
	else if (!ft_strcmp(mini->els->args[0], "pwd"))
		exit_no_err(mini, ft_pwd());
	else if (!ft_strcmp(mini->els->args[0], "export"))
		exit_no_err(mini, ft_export(mini));
	else if (!ft_strcmp(mini->els->args[0], "unset"))
		exit_no_err(mini, ft_unset(mini));
	else if (!ft_strcmp(mini->els->args[0], "env"))
		exit_no_err(mini, ft_env(mini));
	else
		exit_no_err(mini, exec_bin(mini));
}

void	exec_cmd(t_mini *mini)
{
	int	ret;

	ret = 0;
	if (!ft_strcmp(mini->els->args[0], "exit"))
		mini->status = ft_exit(mini);
	else
	{
		g_pid = fork();
		if (!g_pid)
			run_chosen_cmd(mini);
		waitpid(g_pid, &ret, 0);
		mini->status = ret / 256;
	}
}
