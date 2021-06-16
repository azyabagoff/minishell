/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:22:34 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/15 23:42:07 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_env_name(char ***envs, char *name, int size_old)
{
	realloc_2dim_arr(envs, size_old + 1);
	(*envs)[size_old] = ft_strdup(name);
	if (!(*envs))
		exit_err_malloc();
}

static void	set_env_name_val1(char ***envs, char *name,
							char *value, int size_old)
{
	char	*tmp_val;

	tmp_val = NULL;
	realloc_2dim_arr(envs, size_old + 1);
	tmp_val = ft_strjoin(name, "=");
	if (!tmp_val)
		exit_err_malloc();
	if (*value)
	{
		tmp_val = ft__strjoin(tmp_val, value);
		if (!tmp_val)
			exit_err_malloc();
	}
	(*envs)[size_old] = ft_strdup(tmp_val);
	if (!((*envs)[size_old]))
		exit_err_malloc();
	free(tmp_val);
	tmp_val = NULL;
}

static void	set_env_name_val2(char ***envs, char *name, char *value, int ind)
{
	char	*tmp_val;

	tmp_val = NULL;
	free((*envs)[ind]);
	(*envs)[ind] = NULL;
	tmp_val = ft_strjoin(name, "=");
	if (!tmp_val)
		exit_err_malloc();
	if (*value)
	{
		tmp_val = ft__strjoin(tmp_val, value);
		if (!tmp_val)
			exit_err_malloc();
	}
	(*envs)[ind] = ft_strdup(tmp_val);
	if (!((*envs)[ind]))
		exit_err_malloc();
	free(tmp_val);
	tmp_val = NULL;
}

void	set_env(char ***envs, char *name, char *value)
{
	int	count_envs;
	int	ind_env;

	if (!name)
		return ;
	count_envs = count_els_2dim_arr(*envs);
	ind_env = check_env_exists(*envs, name);
	if (ind_env == -1)
	{
		if (!value)
			set_env_name(envs, name, count_envs);
		else
			set_env_name_val1(envs, name, value, count_envs);
	}
	else
	{
		if (value)
			set_env_name_val2(envs, name, value, ind_env);
	}
}
