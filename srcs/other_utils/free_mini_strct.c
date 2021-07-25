/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini_strct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 21:43:33 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/24 18:47:26 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_redirs_list(t_mini *mini)
{
	t_redir	*tmp;
	t_redir	*tmp1;

	tmp = NULL;
	tmp1 = NULL;
	if (mini && mini->start_el && mini->start_el->redir
		&& mini->start_el->redir->r_type != 0)
		tmp = mini->start_el->redir;
	else
	{
		if (mini && mini->start_el && mini->start_el->redir)
			free(mini->start_el->redir);
		return ;
	}
	while (tmp)
	{
		tmp1 = tmp->next;
		if (tmp->file)
			free(tmp->file);
		free(tmp);
		tmp = tmp1;
	}
}

void	free_els(t_els *els)
{
	t_els	*el;

	el = NULL;
	if (els)
	{
		while (els)
		{
			el = els->next;
			free(els);
			els = el;
		}
	}
}

void	free_els_list(t_mini *mini)
{
	t_els	*el;

	el = NULL;
	if (mini->start_el)
	{
		while (mini->start_el)
		{
			el = mini->start_el->next;
			free_2dim_arr(mini->start_el->args);
			free_redirs_list(mini);
			free(mini->start_el);
			mini->start_el = el;
		}
	}
}

void	free_fds_arr(t_mini *mini)
{
	int	i;

	i = 0;
	if (mini->fd)
	{
		while (i < mini->n_els - 1)
		{
			free(mini->fd[i]);
			mini->fd[i] = NULL;
			++i;
		}
		free(mini->fd);
		mini->fd = NULL;
	}
}

void	free_mini_strct(t_mini *mini, int free_envs, int free_echo_n)
{
	if (free_envs)
	{
		if (mini->envs)
		{
			free_2dim_arr(mini->envs);
			mini->envs = NULL;
		}
	}
	close(mini->in_out_fds[0]);
	close(mini->in_out_fds[1]);
	close_all_fds(mini);
	free_fds_arr(mini);
	if (free_echo_n == 2)
	{
		if (mini->echo_n)
			free(mini->echo_n);
		mini->fl_echo_n = 0;
		mini->echo_n = NULL;
	}
	mini->cmd_ind = 0;
	mini->n_els = 0;
	mini->n_els_left = 0;
	free_els_list(mini);
}
