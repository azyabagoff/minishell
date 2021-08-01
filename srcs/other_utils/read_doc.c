/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 19:44:35 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/08/01 20:52:35 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	parse_doc_string(t_mini *mini, char **line, char **doc)
{
	open_envs(mini, line);
	*doc = ft_strjoin1(*doc, *line);
	if (!(*doc))
		exit_err_malloc_mini(mini, NULL, *line);
	free(*line);
	*line = NULL;
	*doc = ft_strjoin1(*doc, "\n");
	if (!(*doc))
		exit_err_malloc_mini(mini, NULL, NULL);
}

char	*read_doc(t_mini *mini, t_redir *red)
{
	char	*line;
	char	*doc;

	signal(SIGINT, heredoc_sig_handler);
	line = NULL;
	doc = NULL;
	while (1)
	{
		line = readline("> ");
		if (!(line))
		{
			ft_putstr_fd("\033[A> ", 1);
			return (doc);
		}
		if (ft_strcmp(line, red->file))
			parse_doc_string(mini, &line, &doc);
		else
			return (doc);
	}
	return (doc);
}

static int	transfer_doc(t_mini *mini, t_redir *red)
{
	int		pid;
	int		status;
	char	*doc;

	doc = NULL;
	pid = 0;
	status = 0;
	if (pipe(red->heredoc_fds))
		exit_err_pipe_mini(mini, NULL, NULL);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
	{
		doc = read_doc(mini, red);
		ft_putstr_fd(doc, red->heredoc_fds[1]);
		close(red->heredoc_fds[1]);
		close(red->heredoc_fds[0]);
		if (doc)
			free(doc);
		exit(0);
	}
	close(red->heredoc_fds[1]);
	wait(&status);
	signal(SIGINT, signal_handler);
	return (status / 256);
}

int	heredoc_read(t_mini *mini)
{
	t_els	*els;
	t_redir	*red;
	char	*doc;
	int		pid;
	int		status;

	pid = 0;
	status = 0;
	doc = NULL;
	red = NULL;
	els = mini->els;
	while (els)
	{
		red = els->redir;
		while (red)
		{
			if (red->r_type == 4)
			{
				mini->status = transfer_doc(mini, red);
				if (mini->status == 1)
				{
					close(red->heredoc_fds[0]);
					return (0);
				}
			}
			red = red->next;
		}
		els = els->next;
	}
	return (1);
}
