/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:19:32 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/21 14:30:12 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_print(char ***envs)
{
	int		i;
	char	**cp_envs;
	char	*name;

	i = 0;
	cp_envs = copy_2dim_arr(*envs);
	name = NULL;
	sort_2dim_arr(&cp_envs);
	while (cp_envs && cp_envs[i])
	{
		ft_putstr_fd("declare -x ", 1);
		name = get_env_name(cp_envs[i]);
		ft_putstr_fd(name, 1);
		if (check_env_has_val(cp_envs[i]))
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(cp_envs[i] + ft_strlen(name) + 1, 1);
			ft_putstr_fd("\"", 1);
		}
		free(name);
		name = NULL;
		ft_putstr_fd("\n", 1);
		++i;
	}
	free_2dim_arr(cp_envs);
}

int	check_correct_id(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = '\0';
	while (str && str[i] && str[i] != '=')
	{
		c = str[i];
		if (i == 0)
		{
			if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
					|| (c == '_')))
				return (0);
		}
		else
		{
			if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
					|| (c >= '0' && c <= '9') || (c == '_')))
				return (0);
		}
		++i;
	}
	return (1);
}

static void	check_id_set_env(char ***envs, char **args, int i)
{
	char	*name;

	name = get_env_name(args[i]);
	if (!check_correct_id(name))
	{
		ft_putstr_fd("minishell: export: `", 1);
		ft_putstr_fd(args[i], 1);
		ft_putstr_fd("': not a valid identifier\n", 1);
	}
	else
	{
		if (check_env_has_val(args[i]))
			set_env(envs, name, args[i] + ft_strlen(name) + 1);
		else
			set_env(envs, name, NULL);
	}
	free(name);
	name = NULL;
}

int	ft_export(char ***envs, char **args)
{
	int		i;

	if (!args[1])
	{
		export_print(envs);
		return (0);
	}
	i = 1;
	while (args && args[i])
	{
		check_id_set_env(envs, args, i);
		++i;
	}
	return (0);
}
