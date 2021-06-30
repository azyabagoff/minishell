/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:14:37 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/30 22:24:14 by sesnowbi         ###   ########.fr       */
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
	if (!ft_strcmp(mini->els->args[0], "exit") && mini->n_els == 1)
		mini->status = ft_exit(mini);
	else if (!ft_strcmp(mini->els->args[0], "exit") && mini->n_els > 1)
		return ;
	else
	{
		g_pid = fork();
		if (!g_pid)
		{
			if (mini->n_els_left < mini->n_els)
				dup2(mini->fd[mini->cmd_ind - 1][0], 0);
			if (mini->els->next)
				dup2(mini->fd[mini->cmd_ind][1], 1);
			close_all_fds(mini);
			run_chosen_cmd(mini);
		}
	}
}
