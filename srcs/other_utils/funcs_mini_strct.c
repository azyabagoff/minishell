/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_mini_strct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:23:01 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/09/16 22:44:52 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_data(t_mini *mini, t_els **neww, char **args, t_list *red_list)
{
	*neww = (t_els *)malloc(sizeof(t_els));
	if (!(*neww))
		exit_err_malloc_mini(mini, NULL, NULL);
	(*neww)->args = copy_2dim_arr(args);
	(*neww)->redir = NULL;
	if (red_list)
		copy_redirs(*neww, red_list);
	if (!(*neww)->redir)
	{
		(*neww)->redir = (t_redir *)malloc(sizeof(t_redir));
		(*neww)->redir->r_type = 0;
		(*neww)->redir->file = NULL;
		(*neww)->redir->next = NULL;
	}
}

void	mini_push_el(t_mini *mini, char **args, t_list *red_list)
{
	t_els	*el;
	t_els	*neww;

	el = NULL;
	copy_data(mini, &neww, args, red_list);
	if (mini->els)
	{
		el = last_el(mini->els);
		el->next = neww;
		neww->next = NULL;
	}
	else
	{
		mini->els = neww;
		neww->next = NULL;
	}
}

t_mini	*ret_mini(void)
{
	static t_mini	mini;

	return (&mini);
}
