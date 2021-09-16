/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 19:49:36 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 20:20:48 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	if_word(t_st *state)
{
	if (state->str[state->i] != ' ' && state->stt == SP)
		return (1);
	return (0);
}

void	do_word(t_st *state, void (*add_stt)(t_st*))
{
	add_sp(state);
	add_stt(0);
	state->stt = NONE;
	state->pos = state->i;
}

void	add_word(t_st *state)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(t_token));
	if (!tk)
		error_parser();
	tk->type = TK_CHAR;
	tk->var = ft_substr(state->str, state->pos, state->i - state->pos);
	if (!tk->var)
		error_parser();
	ft_lstadd_back(&state->token_list, ft_lstnew(tk));
}
