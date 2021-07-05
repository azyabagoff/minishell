/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_mini_strct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 19:23:01 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/05 15:43:57 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_els	*last_el(t_els *el)
{
	if (el)
	{
		while (el->next)
			el = el->next;
		return (el);
	}
	return (NULL);
}

static void	set_redir_file(t_mini *mini, t_els **el, char *file)
{
	if (file && file[0] != '\0')
	{
		(*el)->file = ft_strdup(file);
		if (!(*el)->file)
		{
			free_els(*el);
			exit_err_malloc_mini(mini, NULL, NULL);
		}
	}
	else
		(*el)->file = NULL;
}

void	mini_push_el(t_mini *mini, char **args, int redir_type, char *file)
{
	t_els	*el;
	t_els	*neww;

	el = NULL;
	neww = (t_els *)malloc(sizeof(t_els));
	if (!neww)
		exit_err_malloc_mini(mini, NULL, NULL);
	neww->args = copy_2dim_arr(args);
	neww->redir_type = redir_type;
	set_redir_file(mini, &neww, file);
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
