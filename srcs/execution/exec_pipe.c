/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:14:37 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/09/16 22:05:00 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	run_chosen_cmd_pipe(t_mini *mini)
{
	if (mini->els->args && !mini->els->args[0])
		return ;
	if (!ft_strcmp_low_left(mini->els->args[0], "echo"))
		exit_no_err(mini, ft_echo(mini, mini->els->args));
	else if (!ft_strcmp(mini->els->args[0], "cd"))
		exit_no_err(mini, ft_cd(mini));
	else if (!ft_strcmp_low_left(mini->els->args[0], "pwd"))
		exit_no_err(mini, ft_pwd());
	else if (!ft_strcmp(mini->els->args[0], "export"))
		exit_no_err(mini, ft_export(mini));
	else if (!ft_strcmp(mini->els->args[0], "unset"))
		exit_no_err(mini, ft_unset(mini));
	else if (!ft_strcmp_low_left(mini->els->args[0], "env"))
		exit_no_err(mini, ft_env(mini));
	if (!ft_strcmp(mini->els->args[0], "exit"))
		mini->status = ft_exit(mini);
	else
		exit_no_err(mini, exec_bin_pipe(mini));
}

static int	pipes_redirs_cases(t_mini *mini)
{
	if (mini->n_els_left < mini->n_els)
	{
		close(0);
		dup2(mini->fd[mini->cmd_ind - 1][0], 0);
	}
	if (mini->els->next)
	{
		close(1);
		dup2(mini->fd[mini->cmd_ind][1], 1);
	}
	if (mini->els->redir->r_type != 0)
	{
		if (!exec_redir(mini))
			return (0);
	}
	return (1);
}

void	exec_cmd_pipe(t_mini *mini)
{
	int	block_cmd;

	block_cmd = 0;
	if (mini->els->args[0] && !ft_strcmp(mini->els->args[0], "exit")
		&& mini->n_els > 1)
		return ;
	else
	{
		signal(SIGINT, SIG_IGN);
		mini->pid = fork();
		if (!mini->pid)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (!pipes_redirs_cases(mini))
				block_cmd = 1;
			close(mini->in_out_fds[0]);
			close(mini->in_out_fds[1]);
			close_all_fds(mini);
			if (!block_cmd)
				run_chosen_cmd_pipe(mini);
			else
				exit_no_err(mini, mini->status);
		}
	}
}

static void	wait_children(t_mini *mini, int *ret)
{
	int	i;

	i = 0;
	waitpid(mini->pid, ret, 0);
	while (i < mini->n_els - 1)
	{
		wait(0);
		++i;
	}
	if (WTERMSIG(*ret) == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		mini->status = 130;
	}
	else if (WTERMSIG(*ret) == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		mini->status = 131;
	}
	else
		mini->status = *ret / 256;
	signal(SIGINT, signal_handler);
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
		exec_cmd_pipe(mini);
		--mini->n_els_left;
		++mini->cmd_ind;
		mini->els = mini->els->next;
	}
	close(mini->in_out_fds[0]);
	close(mini->in_out_fds[1]);
	close_all_fds(mini);
	wait_children(mini, &ret);
}
