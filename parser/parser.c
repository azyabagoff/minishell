/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:13:41 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 23:03:22 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_list	*some(t_list *token_list, t_list *temp)
{
	t_token	*tlp;
	t_list	*pred;
	t_token	*tl;

	tl = (t_token *)temp->content;
	pred = list_pred(&token_list, temp);
	tlp = (t_token *)pred->content;
	if ((tlp->type == 4 && ft_strncmp(tl->var, "", 2)) || tlp->type == 5)
	{
		pred = list_pred(&token_list, pred);
		tlp = (t_token *)pred->content;
	}
	if (tlp->type == 1)
	{
		((t_token *)temp->content)->type = 4;
		((t_token *)temp->content)->var = ft_strjoin
			("$", ((t_token *)temp->content)->var);
		temp = temp->next;
		return (temp);
	}
	return (NULL);
}

t_list	*some_else(char *name, t_list *token_list, t_list *temp)
{
	t_list	*we;
	int		i;
	t_token	*r;
	t_list	*s;
	t_list	**list;

	we = NULL;
	s = NULL;
	list = mini_token(name);
	we = *list;
	i = ft_lstsize(we);
	token_list = list_insert(&token_list, temp, we);
	r = (t_token *)temp->content;
	s = temp->next;
	temp = list_del(&token_list, temp);
	while (s && i > 0)
	{
		s = s->next;
		i--;
	}
	temp = temp->next;
	return (s);
}

t_list	*exp_vars(t_list *token_list, t_list *temp, char **env)
{
	t_token	*tl;
	t_list	*we;
	char	*name;

	tl = (t_token *)temp->content;
	name = get_env(env, tl->var);
	we = NULL;
	we = some(token_list, temp);
	if (we)
		return (we);
	if (!name)
		temp = list_del(&token_list, temp);
	else if (tl->type == TK_DVAR)
	{
		free(tl->var);
		tl->var = ft_strdup(name);
		if (!tl->var)
			exit(0);
		tl->type = TK_CHAR;
	}
	else if (tl->type == TK_VAR)
		return (some_else(name, token_list, temp));
	else
		temp = temp->next;
	return (temp);
}

void	expansion_vars(t_list *token_list, char **env)
{
	t_token	*tl;
	t_list	*temp;

	temp = token_list;
	while (temp)
	{
		tl = temp->content;
		if (tl->type == TK_VAR || tl->type == TK_DVAR)
			temp = exp_vars(token_list, temp, env);
		if (temp)
			tl = temp->content;
		if (temp && tl && tl->type != TK_DVAR && tl->type != TK_VAR)
		{
			temp = temp->next;
		}
	}
}

t_list	*parser(char *c, char **envp)
{
	t_list	**token_list;
	t_list	*tmp;
	t_list	*new;
	t_list	*return_list;

	token_list = token(c);
	tmp = *token_list;
	expansion_vars(tmp, envp);
	tmp = connect(tmp);
	file(tmp);
	return_list = NULL;
	new = tmp;
	allocate_memory(tmp, &return_list);
	return_list = fill(&return_list, tmp);
	return (return_list);
}
