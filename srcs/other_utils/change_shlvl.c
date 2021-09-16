/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_shlvl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 15:44:27 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/01 16:00:38 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		++i;
	}
	return (1);
}

void	change_shlvl(t_mini *mini)
{
	char	*cur_env;
	int		lvl;

	lvl = 0;
	cur_env = get_env(mini->envs, "SHLVL");
	if (!cur_env || !is_numeric(cur_env))
		set_env(mini, "SHLVL", "1");
	else
	{
		lvl = ft_atoi(cur_env);
		free(cur_env);
		cur_env = NULL;
		++lvl;
		cur_env = ft_itoa(lvl);
		set_env(mini, "SHLVL", cur_env);
		free(cur_env);
		cur_env = NULL;
	}
}
