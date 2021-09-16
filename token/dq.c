/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 19:45:28 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 20:08:19 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	if_dq(t_st *state)
{
	if (state->stt != SQ && state->str[state->i] == '\"')
		return (1);
	return (0);
}

void	do_dq(t_st *state, void(*add_stt)(t_st *))
{
	add_stt(state);
	if (state->stt == DQ)
		state->stt = NONE;
	else
		state->stt = DQ;
	state->pos = ++state->i;
}
