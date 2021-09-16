/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/08 16:42:21 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 22:12:37 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	file(t_list *tk_list)
{
	struct s_token	*tk;
	int				red;

	red = 0;
	while (tk_list)
	{
		tk = tk_list->content;
		if (red == 1 && tk->type == 4)
		{
			red = 0;
			tk->type = TK_FILE;
			red = 0;
		}
		if (tk->type < 4)
			red = 1;
		tk_list = tk_list->next;
	}
}

static void	push_list(t_list **lst, enum e_token type, void *var)
{
	t_token	*tk;

	tk = malloc(sizeof(struct s_token));
	if (!tk)
	{
		write(2, "Error malloc\n", 13);
		exit(2);
	}
	tk->type = type;
	tk->var = var;
	ft_lstadd_back(lst, ft_lstnew(tk));
}

char	*new_join(char **src, char const *apx)
{
	char	*new_str;
	size_t	src_len;
	size_t	apx_len;

	if (!(*src))
	{
		*src = ft_strdup(apx);
		return (*src);
	}
	src_len = ft_strlen(*src);
	apx_len = ft_strlen(apx);
	new_str = (char *)malloc(sizeof(char) * (src_len + apx_len + 1));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, *src, src_len);
	ft_memcpy(new_str + src_len, apx, apx_len);
	new_str[src_len + apx_len] = '\0';
	free(*src);
	*src = new_str;
	return (new_str);
}

void	in_connect(t_list *tk_list, t_token *tk, char **buff, t_list **new_lst)
{
	tk = tk_list->content;
	if (tk->type == TK_CHAR)
	{
		*buff = new_join(buff, tk->var);
		if (!(*buff))
		{
			write(2, "Error malloc\n", 13);
			exit(2);
		}
	}
	else if (tk->type != TK_CHAR)
	{
		if (*buff)
			push_list(new_lst, TK_CHAR, *buff);
		if (tk->type != TK_SPACE)
			push_list(new_lst, tk->type, tk->var);
		*buff = NULL;
	}
}

t_list	*connect(t_list *tk_list)
{
	t_token			*tk;
	char			*buff;
	t_list			*new_lst;
	const t_list	*root;

	root = tk_list;
	buff = NULL;
	new_lst = NULL;
	tk = NULL;
	while (tk_list)
	{
		in_connect(tk_list, tk, &buff, &new_lst);
		tk_list = tk_list->next;
	}
	if (buff)
		push_list(&new_lst, TK_CHAR, buff);
	ft_lstclear((t_list **)&root, free);
	return (new_lst);
}
