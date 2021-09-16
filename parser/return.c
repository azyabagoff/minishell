/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/17 21:07:24 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 23:03:30 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*get_env(char **envs, char *name)
{
	int		i;
	int		j;
	char	*name1;

	i = 0;
	j = 0;
	name1 = NULL;
	while (envs && envs[i])
	{
		j = 0;
		while (envs[i] && envs[i][j] && envs[i][j] != '=')
			++j;
		if (j < (int)ft_strlen(envs[i]))
		{
			name1 = ft_substr(envs[i], 0, j);
			if (!name1)
				exit(0);
			if (!ft_strcmp(name1, name))
				return (parse_env_val(envs, i, j, name1));
			free(name1);
			name1 = NULL;
		}
		++i;
	}
	return (NULL);
}

t_ret	*malloc_a(int n)
{
	t_ret	*a;

	a = (t_ret *)malloc(sizeof(t_ret));
	a->argv = (char **)malloc(sizeof(char *) * (n + 1));
	if (!a->argv)
	{
		write(2, "Error malloc\n", 13);
		exit(2);
	}
	a->argv[n] = NULL;
	a->rdr_list = NULL;
	return (a);
}

void	null(int *w, int *r, int *f)
{
	*w = 0;
	*r = 0;
	*f = 0;
}

void	check_type(t_token *tk, int *w, int *r, int *f)
{
	if (tk->type == 4)
		*w = *w + 1;
	if (tk->type < 4)
		*r = *r + 1;
	if (tk->type == TK_FILE)
		*f = *f + 1;
}

void	allocate_memory(t_list *list, t_list **return_list)
{
	t_token	*tk;
	int		w;
	int		r;
	int		f;

	null(&w, &r, &f);
	while (list)
	{
		tk = (list)->content;
		check_type(tk, &w, &r, &f);
		if (tk->type == TK_PIPE || !(list->next))
		{
			if (r != f)
			{
				write(2, "Error redirect\n", 15);
				exit(2);
			}
			ft_lstadd_back(return_list, ft_lstnew(malloc_a(w)));
			null(&w, &r, &f);
		}
		list = (list)->next;
	}
}
