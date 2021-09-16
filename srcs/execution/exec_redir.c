/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:29:56 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/08/02 12:39:30 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	exec_redir_trunc_out(t_mini *mini, t_redir *red)
{
	int	fd;

	fd = -1;
	fd = open(red->file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		status_check(red);
		mini->status = 1;
		return (0);
	}
	close(1);
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	exec_redir_append_out(t_mini *mini, t_redir *red)
{
	int	fd;

	fd = -1;
	fd = open(red->file, O_RDWR | O_APPEND | O_CREAT, 0644);
	if (fd == -1)
	{
		status_check(red);
		mini->status = 1;
		return (0);
	}
	close(1);
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	exec_redir_in(t_mini *mini, t_redir *red)
{
	int	fd;

	fd = -1;
	fd = open(red->file, O_RDWR);
	if (fd == -1)
	{
		status_check(red);
		mini->status = 1;
		return (0);
	}
	close(0);
	dup2(fd, 0);
	close(fd);
	return (1);
}

void	exec_redir_heredoc(t_redir *red)
{
	close(0);
	dup2(red->heredoc_fds[0], 0);
	close(red->heredoc_fds[0]);
}

int	exec_redir(t_mini *mini)
{
	t_redir	*red;

	red = mini->els->redir;
	while (red)
	{
		if (red->r_type == 1)
		{
			if (!exec_redir_trunc_out(mini, red))
				return (0);
		}
		else if (red->r_type == 2)
		{
			if (!exec_redir_append_out(mini, red))
				return (0);
		}
		else if (red->r_type == 3)
		{
			if (!exec_redir_in(mini, red))
				return (0);
		}
		else if (red->r_type == 4)
			exec_redir_heredoc(red);
		red = red->next;
	}
	return (1);
}
