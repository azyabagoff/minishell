/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_env_by_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 13:45:18 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/21 14:10:41 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	copy_without_delited(char ***envs, char **old_envs, int ind)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (old_envs && old_envs[i] && i != ind)
	{
		(*envs)[j] = ft_strdup(old_envs[i]);
		if (!(*envs)[j])
			exit_err_malloc(old_envs, NULL);
		++j;
		++i;
	}
	++i;
	while (old_envs && old_envs[i])
	{
		(*envs)[j] = ft_strdup(old_envs[i]);
		if (!(*envs)[j])
			exit_err_malloc(old_envs, NULL);
		++j;
		++i;
	}
}

void	del_env_by_name(char ***envs, char *name)
{
	int		ind;
	int		size_old;
	char	**old_envs;

	size_old = 0;
	old_envs = NULL;
	ind = check_env_exists(*envs, name);
	if (ind != -1)
	{
		size_old = count_els_2dim_arr(*envs);
		old_envs = copy_2dim_arr(*envs);
		free_2dim_arr(*envs);
		*envs = NULL;
		realloc_2dim_arr(envs, size_old - 1);
		copy_without_delited(envs, old_envs, ind);
		free_2dim_arr(old_envs);
		old_envs = NULL;
	}
}
