/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 13:14:37 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/28 20:29:49 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec_cmd(t_mini *mini)
{
	if (!ft_strcmp(mini->els->args[0], "echo"))
		mini->status = ft_echo(mini->els->args);
	else if (!ft_strcmp(mini->els->args[0], "cd"))
		mini->status = ft_cd(mini);
	else if (!ft_strcmp(mini->els->args[0], "pwd"))
		mini->status = ft_pwd();
	else if (!ft_strcmp(mini->els->args[0], "export"))
		mini->status = ft_export(mini);
	else if (!ft_strcmp(mini->els->args[0], "unset"))
		mini->status = ft_unset(mini);
	else if (!ft_strcmp(mini->els->args[0], "env"))
		mini->status = ft_env(mini);
	else if (!ft_strcmp(mini->els->args[0], "exit"))
		mini->status = ft_exit(mini);
	else
		mini->status = exec_bin(mini);
}
