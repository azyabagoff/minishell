/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_uninit_envs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:37:34 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/28 19:06:55 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_uninit_envs(t_mini *mini)
{
	int		i;
	char	*name;
	int		del_flag;

	i = 0;
	name = NULL;
	del_flag = 0;
	while (mini->envs && mini->envs[i])
	{
		if (!check_env_has_val(mini->envs[i]))
		{
			name = get_env_name(mini, mini->envs[i]);
			del_env_by_name(mini, name);
			free(name);
			name = NULL;
			del_flag = 1;
		}
		if (!del_flag)
			++i;
		else
			del_flag = 0;
	}
}
