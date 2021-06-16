/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 20:53:11 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/16 22:28:26 by sesnowbi         ###   ########.fr       */
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
	while (1)
	{
		cp_envp = copy_2dim_arr(envp);
		line = readline("minishell > ");
		args = ft_split(line, ' ');
		free(line);
		line = NULL;
		if (!args || !args[0])
			continue ;
		if (!ft_strcmp(args[0], "echo"))
			g_status = ft_echo(args);
		if (!ft_strcmp(args[0], "cd"))
			g_status = ft_cd(&cp_envp, args);
		free_2dim_arr(args);
		args = NULL;
		free_2dim_arr(cp_envp);
		cp_envp = NULL;
	}
	return (0);
}
