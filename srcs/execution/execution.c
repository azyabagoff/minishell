/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 14:35:40 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/25 17:53:52 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	fork_for_exec_bin_c(t_mini *mini, char *path)
{
	mini->pid = fork();
	if (!mini->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		exit_no_err(mini, execve(path, mini->els->args, mini->envs));
	}
}

void	exec_cmd(t_mini *mini)
{
	if (!ft_strcmp(mini->els->args[0], "echo"))
		mini->status = ft_echo(mini, mini->els->args);
	else if (!ft_strcmp(mini->els->args[0], "cd"))
		mini->status = ft_cd(mini);
	else if (!ft_strcmp(mini->els->args[0], "pwd"))
		mini->status = ft_pwd();
	else if (!ft_strcmp(mini->els->args[0], "export"))
		mini->status = ft_export(mini);
	else if (!ft_strcmp(mini->els->args[0], "unset"))
		mini->status = ft_unset(mini);
	else if (!ft_strcmp(mini->els->args[0], "env"))
		mini->status = ft_env(mini);
	else if (!ft_strcmp(mini->els->args[0], "exit"))
		mini->status = ft_exit(mini);
	else
		mini->status = exec_bin(mini);
}

void	execution(t_mini *mini)
{
	int	block_cmd;

	block_cmd = 0;
	if (mini->n_els > 1)
		exec_pipe(mini);
	else
	{
		while (mini->els)
		{
			if (mini->els->redir->r_type != 0)
			{
				if (!exec_redir(mini))
					block_cmd = 1;
			}
			dup2(mini->in_out_fds[0], 0);
			dup2(mini->in_out_fds[1], 1);
			close(mini->in_out_fds[0]);
			close(mini->in_out_fds[1]);
			if (!block_cmd)
				exec_cmd(mini);
			mini->els = mini->els->next;
		}
	}
}
