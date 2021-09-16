/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_struct_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:08:41 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/09/16 22:10:08 by sesnowbi         ###   ########.fr       */
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

t_redir	*ft_rednew(void *content)
{
	t_redir	*elem;

	elem = NULL;
	elem = (t_redir *)malloc(sizeof(t_redir));
	if (!elem)
		return (NULL);
	elem->r_type = 0;
	if (((t_red *)content)->type == 0)
		elem->r_type = 3;
	if (((t_red *)content)->type == 1)
		elem->r_type = 4;
	if (((t_red *)content)->type == 2)
		elem->r_type = 1;
	if (((t_red *)content)->type == 3)
		elem->r_type = 2;
	elem->file = ft_strdup(((t_red *)content)->word);
	elem->heredoc_fds[0] = -1;
	elem->heredoc_fds[1] = -1;
	elem->next = NULL;
	return (elem);
}

t_redir	*ft_redlast(t_redir *lst)
{
	if (lst)
	{
		while (lst->next)
			lst = lst->next;
		return (lst);
	}
	return (NULL);
}

void	ft_redadd_back(t_redir **lst, t_redir *neww)
{
	t_redir	*el;

	el = NULL;
	if (lst && neww)
	{
		if (*lst)
		{
			el = ft_redlast(*lst);
			el->next = neww;
			neww->next = NULL;
		}
		else
		{
			*lst = neww;
			neww->next = NULL;
		}
	}
}

void	copy_redirs(t_els *els, t_list *red_list)
{
	while (red_list)
	{
		ft_redadd_back(&(els->redir), ft_rednew(red_list->content));
		red_list = red_list->next;
	}
}
