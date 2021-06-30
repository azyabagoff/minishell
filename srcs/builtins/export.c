/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 20:19:32 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/30 22:30:20 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	export_print(t_mini *mini)
{
	int		i;
	char	**cp_envs;
	char	*name;

	i = 0;
	cp_envs = copy_2dim_arr(mini->envs);
	name = NULL;
	sort_2dim_arr(mini, &cp_envs);
	while (cp_envs && cp_envs[i])
	{
		ft_putstr_fd("declare -x ", 1);
		name = get_env_name(mini, cp_envs[i]);
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

static void	check_id_set_env(t_mini *mini, int i)
{
	char	*name;

	name = get_env_name(mini, mini->els->args[i]);
	if (!check_correct_id(name))
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(mini->els->args[i], 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else
	{
		if (check_env_has_val(mini->els->args[i]))
			set_env(mini, name,
				mini->els->args[i] + ft_strlen(name) + 1);
		else
			set_env(mini, name, NULL);
	}
	free(name);
	name = NULL;
}

int	ft_export(t_mini *mini)
{
	int		i;

	if (!mini->els->args[1])
	{
		export_print(mini);
		return (0);
	}
	i = 1;
	while (mini->els->args && mini->els->args[i])
	{
		check_id_set_env(mini, i);
		++i;
	}
	return (0);
}
