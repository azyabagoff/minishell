/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_exists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 22:17:40 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/15 23:25:09 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_env_exists(char **envs, char *name)
{
	int		i;
	char	*cur_env_name;

	i = 0;
	cur_env_name = NULL;
	while (envs && envs[i])
	{
		cur_env_name = get_env_name(envs[i]);
		if (!ft_strcmp(cur_env_name, name))
			return (i);
		free(cur_env_name);
		cur_env_name = NULL;
		++i;
	}
	return (-1);
}
