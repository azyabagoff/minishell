/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 20:02:27 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 20:21:24 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	if_var(t_st *state)
{
	if ((state->stt == DVAR || state->stt == VAR)
		&& !(ft_isalnum(state->str[state->i]))
		&& state->str[state->i] != '_')
		return (1);
	return (0);
}

int	if_pre_var(t_st *state)
{
	if (state->stt != SQ && state->str[state->i] == '$')
		return (1);
	return (0);
}

void	do_pre_var(t_st *state, void (*add_stt)(t_st*))
{
	add_stt(state);
	state->pos = ++state->i;
	if (state->stt == DQ)
		state->stt = DVAR;
	else
		state->stt = VAR;
	if (state->str[state->i] == '?')
	{
		state->i++;
		add_var(state);
		state->pos = state->i;
		if (state->stt == DVAR)
			state->stt = DQ;
		else
			state->stt = NONE;
	}
}

void	do_var(t_st *state, void (*add_stt)(t_st*))
{
	if (state->pos == state->i)
	{
		state->pos--;
		add_word(state);
	}
	else
		add_stt(state);
	if (state->stt == DVAR)
		state->stt = DQ;
	else
		state->stt = NONE;
	state->pos = state->i;
}

void	add_var(t_st *state)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(t_token));
	if (!tk)
		error_parser();
	if (state->stt == VAR)
		tk->type = TK_VAR;
	else
		tk->type = TK_DVAR;
	tk->var = ft_substr(state->str, state->pos, state->i - state->pos);
	if (!tk->var)
		error_parser();
	ft_lstadd_back(&state->token_list, ft_lstnew(tk));
}
