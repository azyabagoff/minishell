/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 19:55:13 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/16 19:47:01 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_echo(char **args)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (args[++i])
	{
		if (i == 1)
		{
			if (!ft_strcmp(args[i], "-n"))
				flag = 1;
			else
				ft_putstr_fd(args[i], 1);
		}
		else if (i == 2 && flag)
			ft_putstr_fd(args[i], 1);
		else
		{
			ft_putstr_fd(" ", 1);
			ft_putstr_fd(args[i], 1);
		}
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
