/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_put_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:32:20 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/09/16 22:06:13 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_put_status(t_mini *mini, char ***args)
{
	int		j;

	j = 0;
	while (*args && (*args)[j])
	{
		if (!ft_strcmp((*args)[j], "$?"))
		{
			free((*args)[j]);
			(*args)[j] = ft_lltoa(mini->status);
			if (!(*args)[j])
				exit_err_malloc_mini(mini, NULL, NULL);
		}
		++j;
	}
}

void	status_check(t_redir *red)
{
	struct stat	buff;

	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(red->file, 2);
	if (!stat(red->file, &buff))
	{
		if (buff.st_mode & S_IFDIR)
			ft_putendl_fd(": Is a directory", 2);
		else
			ft_putendl_fd(": Permission denied", 2);
	}
	else
		ft_putendl_fd(": No such file or directory", 2);
}
