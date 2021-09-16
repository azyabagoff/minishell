/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 19:40:44 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 20:38:27 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	if_pipe(t_st *state)
{
	if (state->stt != SQ && state->stt != DQ && state->str[state->i] == '|')
		return (1);
	return (0);
}

void	do_pipe(t_st *state, void (*add_stt)(t_st*))
{
	add_stt(state);
	add_pipe(state);
	state->pos = ++state->i;
	state->stt = NONE;
}

void	add_pipe(t_st *state)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(t_token));
	if (!tk)
		error_parser();
	tk->type = TK_PIPE;
	tk->var = NULL;
	ft_lstadd_back(&state->token_list, ft_lstnew(tk));
}
