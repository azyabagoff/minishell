/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini_strct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 21:43:33 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/01 15:14:49 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			if (mini->start_el->file)
				free(mini->start_el->file);
			free(mini->start_el);
			mini->start_el = el;
		}
	}
}

void	free_fds_arr(t_mini *mini)
{
	int	i;

	i = 0;
	while (i < mini->n_els - 1)
	{
		free(mini->fd[i]);
		mini->fd[i] = NULL;
		++i;
	}
	free(mini->fd);
	mini->fd = NULL;
}

void	free_mini_strct(t_mini *mini, int free_envs)
{
	if (free_envs)
	{
		if (mini->envs)
		{
			free_2dim_arr(mini->envs);
			mini->envs = NULL;
		}
	}
	close_all_fds(mini);
	free_fds_arr(mini);
	mini->cmd_ind = 0;
	mini->n_els = 0;
	mini->n_els_left = 0;
	free_els_list(mini);
}
