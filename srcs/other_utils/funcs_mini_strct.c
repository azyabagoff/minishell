/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_mini_strct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:23:01 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/16 18:00:03 by sesnowbi         ###   ########.fr       */
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

// static void	set_redir_file(t_mini *mini, t_els **el, char *file)
// {
// 	if (file && file[0] != '\0')
// 	{
// 		(*el)->redir->file = ft_strdup(file);
// 		if (!(*el)->redir->file)
// 		{
// 			free_els(*el);
// 			exit_err_malloc_mini(mini, NULL, NULL);
// 		}
// 	}
// 	else
// 		(*el)->redir->file = NULL;
// }

void	mini_push_el(t_mini *mini, char **args)///добавить в аргументы список редиректов
{
	t_els	*el;
	t_els	*neww;

	el = NULL;
	neww = (t_els *)malloc(sizeof(t_els));
	if (!neww)
		exit_err_malloc_mini(mini, NULL, NULL);
	neww->args = copy_2dim_arr(args);
	neww->redir = (t_redir *)malloc(sizeof(t_redir));//заменить на иниц. списка редиректов
	neww->redir->r_type = 0;//заменить на иниц. списка редиректов
	neww->redir->file = NULL;//заменить на иниц. списка редиректов
	neww->redir->redir_fd = 1;//заменить на иниц. списка редиректов
	neww->redir->next = NULL;//заменить на иниц. списка редиректов
	neww->next = NULL;
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
