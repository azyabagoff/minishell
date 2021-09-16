/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 19:14:57 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 23:03:39 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdlib.h>
# include <stdio.h>
# include "../token/token.h"

typedef struct s_ret
{
	char				**argv;
	t_list				*rdr_list;
}						t_ret;

typedef struct s_red
{
	int					type;
	char				*word;
}						t_red;

void	expansion_vars(t_list *token_list, char **env);
t_list	*list_insert(t_list **list, t_list *temp, t_list *insert);
t_list	*list_del(t_list **list, t_list *temp);
t_list	*list_pred(t_list **list, t_list *temp);
t_list	**mini_token(char *line);
t_list	*list_pred(t_list **list, t_list *temp);
t_list	*connect(t_list *tk_list);
void	file(t_list *tk_list);
void	allocate_memory(t_list *list, t_list **return_list);
t_list	*fill(t_list **return_list, t_list *list);
t_list	*parser(char *c, char **envp);
char	*parse_env_val(char **envs, int i, int j, char *var_to_free);
char	*get_env(char **envs, char *name);

#endif