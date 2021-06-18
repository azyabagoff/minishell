/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 14:08:34 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/18 16:24:52 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_envs(char **envs, int pr_uninit)
{
	int		i;

	i = 0;
	while (envs && envs[i])
	{
		if (!pr_uninit)
		{
			if (!check_env_has_val(envs[i]))
			{
				++i;
				continue ;
			}
		}
		ft_putstr_fd(envs[i], 1);
		ft_putstr_fd("\n", 1);
		++i;
	}
}

int	ft_env(char **envs, char **args)
{
	if (args[1])
	{
		ft_putstr_fd(
			"minishell: env: arguments and options are not supported\n", 1);
		return (1);
	}
	print_envs(envs, 0);
	return (0);
}
