/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 19:45:53 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 20:37:48 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	if_red(t_st *state)
{
	if (state->stt != DQ && state->stt != SQ
		&& (state->str[state->i] == '<' || state->str[state->i] == '>'))
		return (1);
	return (0);
}

void	add_rd(t_st *state, enum e_token tok)
{
	t_token	*tk;

	tk = (t_token *)malloc(sizeof(t_token));
	if (!tk)
		error_parser();
	tk->type = tok;
	tk->var = NULL;
	ft_lstadd_back(&state->token_list, ft_lstnew(tk));
}

void	do_red(t_st *state, void (*add_stt)(t_st*))
{
	add_stt(state);
	if (state->str[state->i] == '>')
	{
		if (state->str[state->i + 1] == '>')
		{
			add_rd(state, TK_RR);
			state->i++;
		}
		else
			add_rd(state, TK_R);
	}
	else
	{
		if (state->str[state->i + 1] == '<')
		{
			add_rd(state, TK_LL);
			state->i++;
		}
		else
			add_rd(state, TK_L);
	}
	state->i++;
	state->pos = state->i;
}
