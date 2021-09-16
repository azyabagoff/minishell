/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 21:46:55 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 21:59:11 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
t_red	*ret_red(t_list *list)
{
	t_token	*tk;
	t_red	*r;

	r = (t_red *)malloc(sizeof(t_red));
	tk = (t_token *)(list)->content;
	r->type = (int)tk->type;
	tk = (list->next)->content;
	r->word = ft_substr(tk->var, 0, ft_strlen(tk->var));
	return (r);
}

static void	null(int *w, int *r, int *i)
{
	*w = 0;
	*r = 0;
	*i = 0;
}

void	in_fill(t_list **return_list, t_token *tk, int *i, t_list **list)
{
	if (tk->type == 4)
	{
		((t_ret *)((*return_list)->content))->argv[*i] = ft_substr
			(tk->var, 0, ft_strlen(tk->var));
		*i = *i + 1;
	}
	if (tk->type < 4)
	{
		ft_lstadd_back(&(((t_ret *)((*return_list)->content))->rdr_list),
			ft_lstnew(ret_red(*list)));
		*list = (*list)->next;
	}
}

t_list	*fill(t_list **return_list, t_list *list)
{
	t_token	*tk;
	int		w;
	int		r;
	int		i;
	t_list	*elem;

	null(&w, &r, &i);
	elem = *return_list;
	while (list)
	{
		tk = (list)->content;
		in_fill(return_list, tk, &i, &list);
		if (tk->type == TK_PIPE || !(list->next))
		{
			((t_ret *)((*return_list)->content))->argv[i] = NULL;
			i = 0;
			*return_list = (*return_list)->next;
		}
		list = (list)->next;
	}
	return (elem);
}
