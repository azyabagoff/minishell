/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 19:05:03 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/17 19:40:32 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		ft_putstr_fd("minishell: pwd: ", 1);
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 1);
		return (1);
	}
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	free(path);
	path = NULL;
	return (0);
}
