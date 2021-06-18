/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:45:37 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/18 13:58:34 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_unset(char ***envs, char **args)
{
	int		i;

	if (!args[1])
		return (0);
	i = 1;
	while (args && args[i])
	{
		if (!check_correct_id(args[i]))
		{
			ft_putstr_fd("minishell: unset: `", 1);
			ft_putstr_fd(args[i], 1);
			ft_putstr_fd("': not a valid identifier\n", 1);
		}
		else
			del_env_by_name(envs, args[i]);
		++i;
	}
	return (0);
}
