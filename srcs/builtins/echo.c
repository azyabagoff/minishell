/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 19:55:13 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/18 16:53:30 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo_cases(char *str, int *flag, int i)
{
	if (i == 1)
	{
		if (!ft_strcmp(str, "-n"))
			*flag = 1;
		else
			ft_putstr_fd(str, 1);
	}
	else if (i == 2 && *flag)
		ft_putstr_fd(str, 1);
	else
	{
		ft_putstr_fd(" ", 1);
		ft_putstr_fd(str, 1);
	}
}

int	ft_echo(char **args)
{
	int		i;
	int		flag;

	i = 0;
	flag = 0;
	while (args[++i])
		echo_cases(args[i], &flag, i);
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}
