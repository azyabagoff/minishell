/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 20:53:11 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/18 21:27:01 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	*line;
	char	**args;
	char	**cp_envp;

	(void)argc;
	(void)argv;
	args = NULL;
	cp_envp = NULL;
	line = NULL;
	cp_envp = copy_2dim_arr(envp);
	while (1)
	{
		line = readline("minishell > ");
		args = ft_split(line, ' ');
		free(line);
		line = NULL;
		if (!args || !args[0])
			continue ;
		if (!ft_strcmp(args[0], "echo"))
			g_status = ft_echo(args);
		else if (!ft_strcmp(args[0], "cd"))
			g_status = ft_cd(&cp_envp, args);
		else if (!ft_strcmp(args[0], "pwd"))
			g_status = ft_pwd();
		else if (!ft_strcmp(args[0], "export"))
			g_status = ft_export(&cp_envp, args);
		else if (!ft_strcmp(args[0], "unset"))
			g_status = ft_unset(&cp_envp, args);
		else if (!ft_strcmp(args[0], "env"))
			g_status = ft_env(cp_envp, args);
		else if (!ft_strcmp(args[0], "exit"))
			g_status = ft_exit(&cp_envp, &args);
		free_2dim_arr(args);
		args = NULL;
	}
	return (0);
}
