/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:14:37 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/03 17:42:16 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_chosen_cmd_pipe(t_mini *mini)
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
	if (!ft_strcmp(mini->els->args[0], "exit"))
		mini->status = ft_exit(mini);
	else
		exit_no_err(mini, exec_bin_pipe(mini));
}

void	exec_cmd_pipe(t_mini *mini)
{
	if (!ft_strcmp(mini->els->args[0], "exit") && mini->n_els > 1)
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
			run_chosen_cmd_pipe(mini);
		}
	}
}

static void	wait_children(t_mini *mini, int *ret)
{
	int	i;

	i = 0;
	waitpid(g_pid, ret, 0);
	while (i < mini->n_els - 1)
	{
		wait(0);
		++i;
	}
	mini->status = *ret / 256;
}

void	exec_pipe(t_mini *mini)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < mini->n_els - 1)
	{
		if (pipe(mini->fd[i]) == -1)
			exit_err_pipe_mini(mini, NULL, NULL);
		++i;
	}
	while (mini->els)
	{
		if (!mini->els->redir_type)//заменю на проверку на налл в пуш елемент из викиной структуры
			exec_cmd_pipe(mini);
		else
			exec_redir(mini);
		--mini->n_els_left;
		++mini->cmd_ind;
		mini->els = mini->els->next;
	}
	close_all_fds(mini);
	wait_children(mini, &ret);
}
