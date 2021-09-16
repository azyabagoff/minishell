/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:45:37 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/30 21:39:56 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(t_mini *mini)
{
	int		i;

	if (!mini->els->args[1])
		return (0);
	i = 1;
	while (mini->els->args && mini->els->args[i])
	{
		if (!check_correct_id(mini->els->args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(mini->els->args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else
			del_env_by_name(mini, mini->els->args[i]);
		++i;
	}
	return (0);
}
