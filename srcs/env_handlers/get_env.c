/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:54:29 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/28 19:09:08 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*parse_env_val(t_mini *mini, int i, int j, char *var_to_free)
{
	char	*val;

	free(var_to_free);
	val = NULL;
	if (mini->envs[i][j + 1] == '\0')
	{
		val = ft_strdup("\0");
		if (!val)
			exit_err_malloc(mini, NULL, NULL);
	}
	else
	{
		val = ft_substr(mini->envs[i], j + 1, ft_strlen(mini->envs[i]) - j - 1);
		if (!val)
			exit_err_malloc(mini, NULL, NULL);
	}
	return (val);
}

char	*get_env(t_mini *mini, char *name)
{
	int		i;
	int		j;
	char	*name1;

	i = 0;
	j = 0;
	name1 = NULL;
	while (mini->envs && mini->envs[i])
	{
		j = 0;
		while (mini->envs[i][j] && mini->envs[i][j] != '=')
			++j;
		if (j < (int)ft_strlen(mini->envs[i]))
		{
			name1 = ft_substr(mini->envs[i], 0, j);
			if (!name1)
				exit_err_malloc(mini, NULL, NULL);
			if (!ft_strcmp(name1, name))
				return (parse_env_val(mini, i, j, name1));
			free(name1);
			name1 = NULL;
		}
		++i;
	}
	return (NULL);
}

char	*get_env_name(t_mini *mini, char *env)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (env[i] && env[i] != '=')
		++i;
	name = ft_substr(env, 0, i);
	if (!name)
		exit_err_malloc(mini, NULL, NULL);
	return (name);
}
