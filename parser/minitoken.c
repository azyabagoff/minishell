/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitoken.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/07 12:43:54 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 23:01:07 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char	*parse_env_val(char **envs, int i, int j, char *var_to_free)
{
	char	*val;

	free(var_to_free);
	val = NULL;
	if (envs[i][j + 1] == '\0')
	{
		val = ft_strdup("\0");
		if (!val)
			exit(0);
	}
	else
	{
		val = ft_substr(envs[i], j + 1, ft_strlen(envs[i]) - j - 1);
		if (!val)
			exit(0);
	}
	return (val);
}

static void	state_init(t_st *state, char *line)
{
	state->i = 0;
	state->pos = 0;
	state->str = line;
	state->stt = NONE;
	state->token_list = NULL;
	state->flag = 1;
}

static void	to_do_func(t_func *func)
{
	func->if_stt[0] = &if_sp;
	func->if_stt[1] = &if_word;
	func->if_stt[2] = &if_end;
	func->if_stt[3] = &if_none;
	func->add_stt[0] = &add_none;
	func->add_stt[1] = &add_word;
	func->add_stt[2] = &add_sp;
	func->add_stt[3] = &add_pipe;
	func->add_stt[4] = &add_word;
	func->add_stt[5] = &add_word;
	func->add_stt[6] = &add_var;
	func->add_stt[7] = &add_var;
}

static void	to_do_do(t_do *dodo)
{
	dodo->do_stt[0] = &do_sp;
	dodo->do_stt[1] = &do_word;
	dodo->do_stt[2] = &do_end;
	dodo->do_stt[3] = &do_none;
}

t_list	**mini_token(char *line)
{
	t_st	state;
	t_func	func;
	t_do	dodo;
	int		k;

	state_init(&state, line);
	to_do_do(&dodo);
	to_do_func(&func);
	while (state.flag == 1)
	{
		k = 0;
		while (k < 4)
		{
			if (func.if_stt[k](&state) == 1)
			{
				dodo.do_stt[k](&state, *func.add_stt[state.stt]);
				break ;
			}
			k++;
		}
		if (k == 4)
			state.i++;
	}
	return (&(&state)->token_list);
}
