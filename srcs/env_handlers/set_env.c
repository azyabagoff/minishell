/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:22:34 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/29 18:52:47 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_env_name(t_mini *mini, char *name, int size_old)
{
	realloc_2dim_arr(mini, size_old + 1);
	mini->envs[size_old] = ft_strdup(name);
	if (!mini->envs)
		exit_err_malloc_mini(mini, NULL, NULL);
}

static void	set_env_name_val1(t_mini *mini, char *name,
							char *value, int size_old)
{
	char	*tmp_val;

	tmp_val = NULL;
	realloc_2dim_arr(mini, size_old + 1);
	tmp_val = ft_strjoin(name, "=");
	if (!tmp_val)
		exit_err_malloc_mini(mini, NULL, NULL);
	if (*value)
	{
		tmp_val = ft__strjoin(tmp_val, value);
		if (!tmp_val)
			exit_err_malloc_mini(mini, NULL, NULL);
	}
	mini->envs[size_old] = ft_strdup(tmp_val);
	if (!(mini->envs[size_old]))
		exit_err_malloc_mini(mini, NULL, tmp_val);
	free(tmp_val);
	tmp_val = NULL;
}

static void	set_env_name_val2(t_mini *mini, char *name, char *value, int ind)
{
	char	*tmp_val;

	tmp_val = NULL;
	free(mini->envs[ind]);
	mini->envs[ind] = NULL;
	tmp_val = ft_strjoin(name, "=");
	if (!tmp_val)
		exit_err_malloc_mini(mini, NULL, NULL);
	if (*value)
	{
		tmp_val = ft__strjoin(tmp_val, value);
		if (!tmp_val)
			exit_err_malloc_mini(mini, NULL, NULL);
	}
	mini->envs[ind] = ft_strdup(tmp_val);
	if (!(mini->envs[ind]))
		exit_err_malloc_mini(mini, NULL, tmp_val);
	free(tmp_val);
	tmp_val = NULL;
}

void	set_env(t_mini *mini, char *name, char *value)
{
	int	count_envs;
	int	ind_env;

	if (!name)
		return ;
	count_envs = count_els_2dim_arr(mini->envs);
	ind_env = check_env_exists(mini, name);
	if (ind_env == -1)
	{
		if (!value)
			set_env_name(mini, name, count_envs);
		else
			set_env_name_val1(mini, name, value, count_envs);
	}
	else
	{
		if (value)
			set_env_name_val2(mini, name, value, ind_env);
	}
}
