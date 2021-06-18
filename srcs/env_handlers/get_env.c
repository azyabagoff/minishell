/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:54:29 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/18 21:57:50 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*parse_env_val(char **envs, int i, int j)
{
	char	*val;

	val = NULL;
	if (envs[i][j + 1] == '\0')
	{
		val = ft_strdup("\0");
		if (!val)
			exit_err_malloc();
	}
	else
	{
		val = ft_substr(envs[i], j + 1, ft_strlen(envs[i]) - j - 1);
		if (!val)
			exit_err_malloc();
	}
	return (val);
}

char	*get_env(char **envs, char *name)
{
	int		i;
	int		j;
	char	*name1;

	i = 0;
	j = 0;
	name1 = NULL;
	while (envs && envs[i])
	{
		j = 0;
		while (envs[i][j] && envs[i][j] != '=')
			++j;
		if (j < (int)ft_strlen(envs[i]))
		{
			name1 = ft_substr(envs[i], 0, j);
			if (!name1)
				exit_err_malloc();
			if (!ft_strcmp(name1, name))
				return (parse_env_val(envs, i, j));
			free(name1);
			name1 = NULL;
		}
		++i;
	}
	return (NULL);
}

char	*get_env_name(char *env)
{
	int		i;
	char	*name;

	i = 0;
	name = NULL;
	while (env[i] && env[i] != '=')
		++i;
	name = ft_substr(env, 0, i);
	if (!name)
		exit_err_malloc();
	return (name);
}
