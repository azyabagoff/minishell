/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_mini_strct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:23:01 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/08/01 18:17:34 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_els	*last_el(t_els *el)
{
	if (el)
	{
		while (el->next)
			el = el->next;
		return (el);
	}
	return (NULL);
}

void	mini_push_el(t_mini *mini, char **args)///добавить в аргументы список редиректов
{
	t_els	*el;
	t_els	*neww;
	// t_redir	*tmp1;///
	// t_redir	*tmp2;///
	// t_redir	*tmp3;///

	el = NULL;
	neww = (t_els *)malloc(sizeof(t_els));
	if (!neww)
		exit_err_malloc_mini(mini, NULL, NULL);
	neww->args = copy_2dim_arr(args);
	///заменить на иниц. списка редиректов
	neww->redir = (t_redir *)malloc(sizeof(t_redir));//
	neww->redir->r_type = 4;//
	neww->redir->file = ft_strdup("q");//
	neww->redir->next = NULL;//
	// tmp1 = (t_redir *)malloc(sizeof(t_redir));
	// tmp1->r_type = 2;
	// tmp1->file = ft_strdup("a");
	// tmp2 = (t_redir *)malloc(sizeof(t_redir));
	// tmp2->r_type = 1;
	// tmp2->file = ft_strdup("b");
	// tmp1->next = tmp2;
	// tmp3 = (t_redir *)malloc(sizeof(t_redir));
	// tmp3->r_type = 3;
	// tmp3->file = ft_strdup("c");
	// tmp2->next = tmp3;
	// tmp3->next = NULL;
	// neww->redir->next = tmp1;
	///
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
