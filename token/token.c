/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 18:04:52 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 20:34:42 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include <stdio.h>

void	state_init(t_st *state, char *line)
{
	state->i = 0;
	state->pos = 0;
	state->str = line;
	state->stt = NONE;
	state->token_list = NULL;
	state->flag = 1;
}

void	just_do_do(t_do *dodo)
{
	dodo->do_stt[0] = &do_var;
	dodo->do_stt[1] = &do_sp;
	dodo->do_stt[2] = &do_pipe;
	dodo->do_stt[3] = &do_sq;
	dodo->do_stt[4] = &do_dq;
	dodo->do_stt[5] = &do_word;
	dodo->do_stt[6] = &do_pre_var;
	dodo->do_stt[7] = &do_red;
	dodo->do_stt[8] = &do_end;
	dodo->do_stt[9] = &do_none;
}

void	just_do_func(t_func *func)
{
	func->if_stt[0] = &if_var;
	func->if_stt[1] = &if_sp;
	func->if_stt[2] = &if_pipe;
	func->if_stt[3] = &if_sq;
	func->if_stt[4] = &if_dq;
	func->if_stt[5] = &if_word;
	func->if_stt[6] = &if_pre_var;
	func->if_stt[7] = &if_red;
	func->if_stt[8] = &if_end;
	func->if_stt[9] = &if_none;
	func->add_stt[0] = &add_none;
	func->add_stt[1] = &add_word;
	func->add_stt[2] = &add_sp;
	func->add_stt[3] = &add_pipe;
	func->add_stt[4] = &add_word;
	func->add_stt[5] = &add_word;
	func->add_stt[6] = &add_var;
	func->add_stt[7] = &add_var;
}

t_list	**token(char *line)
{
	t_st	state;
	t_func	func;
	t_do	dodo;
	int		k;

	state_init(&state, line);
	just_do_func(&func);
	just_do_do(&dodo);
	while (state.flag == 1)
	{
		k = 0;
		while (k < 10)
		{
			if (func.if_stt[k](&state) == 1)
			{
				dodo.do_stt[k](&state, *func.add_stt[state.stt]);
				break ;
			}
			k++;
		}
		if (k == 10)
			state.i++;
	}
	return (&(&state)->token_list);
}
