/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini_strct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 21:43:33 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/28 21:44:06 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			free(mini->start_el);
			mini->start_el = el;
		}
	}
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
	free_els_list(mini);
}
