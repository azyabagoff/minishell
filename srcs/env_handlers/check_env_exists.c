/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_exists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 22:17:40 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/28 19:03:56 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_env_exists(t_mini *mini, char *name)
{
	int		i;
	char	*cur_env_name;

	i = 0;
	cur_env_name = NULL;
	while (mini->envs && mini->envs[i])
	{
		cur_env_name = get_env_name(mini, mini->envs[i]);
		if (!ft_strcmp(cur_env_name, name))
		{
			free(cur_env_name);
			cur_env_name = NULL;
			return (i);
		}
		free(cur_env_name);
		cur_env_name = NULL;
		++i;
	}
	return (-1);
}
