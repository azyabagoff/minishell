/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 19:44:35 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/31 17:27:21 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sig_heredoc(void)
{
	signal(SIGINT, heredoc_sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

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

void	read_doc(t_mini *mini, t_redir *red, char **doc)//сигналы + не работает в пайпах
{
	char	*line;

	sig_heredoc();
	line = NULL;
	while (1)
	{
		line = readline("> ");
		if (!(line))
		{
			ft_putstr_fd("\033[A> ", 1);
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, signal_handler);
			return ;
		}
		if (ft_strcmp(line, red->file))
			parse_doc_string(mini, &line, doc);
		else
		{
			signal(SIGQUIT, SIG_IGN);
			signal(SIGINT, signal_handler);
			return ;
		}
	}
}
