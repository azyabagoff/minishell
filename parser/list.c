/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 21:40:46 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 21:45:47 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_tok(void *tok)
{
	t_token	*tk;

	tk = tok;
	free(tk->var);
	free(tk);
}

t_list	*list_pred(t_list **list, t_list *temp)
{
	t_list	*new;
	t_list	*ret;

	ret = *list;
	if (temp == *list)
		return (temp);
	else
	{
		new = *list;
		while (new->next != temp)
		{
			new = new->next;
		}
		return (new);
	}
}

void	in_list_del(t_list *temp)
{
	free_tok(temp->content);
	temp->next = NULL;
	free(temp);
}

t_list	*list_del(t_list **list, t_list *temp)
{
	t_list	*new;
	t_list	*new2;
	t_list	*ret;

	ret = *list;
	if (temp == *list)
	{
		new = (*list)->next;
		in_list_del(temp);
		*list = new;
	}
	else
	{
		new = *list;
		while (new->next != temp)
			new = new->next;
		new2 = new->next;
		new2 = new2->next;
		new->next = new2;
		free_tok(temp->content);
		temp->next = NULL;
		free(temp);
	}
	return (ret);
}

t_list	*list_insert(t_list **list, t_list *temp, t_list *insert)
{
	t_list	*new;
	t_list	*ret;

	ret = *list;
	if (!(*list) && insert)
		*list = insert;
	else if (!insert)
		return (NULL);
	else if (!temp)
	{
		while (insert->next)
			insert = insert->next;
		ft_lstadd_front(list, insert);
	}
	else
	{
		new = insert;
		while (new->next)
			new = new->next;
		new->next = temp->next;
		temp->next = insert;
	}
	return (ret);
}
