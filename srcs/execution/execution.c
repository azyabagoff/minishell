/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 14:35:40 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/30 22:16:02 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execution(t_mini *mini)
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
			exec_cmd(mini);
		else
			exec_redir(mini);
		--mini->n_els_left;
		++mini->cmd_ind;
		mini->els = mini->els->next;
	}
	close_all_fds(mini);
	waitpid(g_pid, &ret, 0);
	mini->status = ret / 256;
}
