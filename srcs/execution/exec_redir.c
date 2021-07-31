/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 14:29:56 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/31 19:25:19 by sesnowbi         ###   ########.fr       */
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

int	exec_redir_heredoc(t_mini *mini, t_redir *red)
{
	int		fds[2];
	char	*doc;

	doc = NULL;
	if (pipe(fds) == -1)
		exit_err_pipe_mini(mini, NULL, NULL);
	read_doc(mini, red, &doc);
	close(0);
	dup2(fds[0], 0);
	close(fds[0]);
	ft_putstr_fd(doc, fds[1]);
	free(doc);
	close(fds[1]);
	return (1);
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
			exec_redir_heredoc(mini, red);
		red = red->next;
	}
	return (1);
}
