/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edread <edread@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 19:59:06 by edread            #+#    #+#             */
/*   Updated: 2021/09/16 20:46:50 by edread           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"

int	if_end(t_st *state)
{
	if (state->str[state->i] == '\0')
		return (1);
	return (0);
}

int	if_none(t_st *state)
{
	if (state->stt == NONE)
		return (1);
	return (0);
}

void	do_end(t_st *state, void (*add_stt)(t_st*))
{
	add_stt(state);
	state->i++;
	state->flag = 0;
}

void	do_none(t_st *state, void (*add_stt)(t_st*))
{
	add_stt(0);
	state->stt = W;
}

void	add_none(t_st *state)
{
	(void)state;
}
