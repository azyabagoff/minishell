/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 14:35:40 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/28 17:56:01 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	execution(t_mini *mini)
{
	while (mini->els)
	{
		exec_cmd(mini);
		mini->els = mini->els->next;
	}
	free_mini_strct(mini, 0);
}
