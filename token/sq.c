/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sq.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 19:44:38 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 20:36:39 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	if_sq(t_st *state)
{
	if (state->stt != DQ && state->str[state->i] == '\'')
		return (1);
	return (0);
}

void	do_sq(t_st *state, void (*add_stt)(t_st*))
{
	add_stt(state);
	if (state->stt == SQ)
		state->stt = NONE;
	else
		state->stt = SQ;
	state->pos = ++state->i;
}
