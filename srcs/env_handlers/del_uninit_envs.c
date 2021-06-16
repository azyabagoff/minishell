/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_uninit_envs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:37:34 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/16 16:07:25 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_uninit_envs(char ***envs)
{
	int		i;
	char	*name;
	int		del_flag;

	i = 0;
	name = NULL;
	del_flag = 0;
	while (*envs && (*envs)[i])
	{
		if (!check_env_has_val((*envs)[i]))
		{
			name = get_env_name((*envs)[i]);
			del_env_by_name(envs, name);
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
