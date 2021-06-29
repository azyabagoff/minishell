/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 20:53:11 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/29 22:15:22 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	char		**args;
	char		**args1;
	int			i;
	int			j;
	t_mini		mini;

	(void)argc;
	(void)argv;
	mini.els = NULL;
	args = NULL;
	args1 = NULL;
	line = NULL;
	i = 0;
	j = 0;
	mini.envs = copy_2dim_arr(envp);
	mini.status = 0;
	while (1)
	{
		line = readline("minishell > ");//
		if (line && line[0])//
			add_history(line);//
		args = ft_split(line, '|');//
		free(line);//
		line = NULL;//
		if (!args)//
			continue ;//
		if (!args[0])//
		{//
			free(args);//
			continue ;//
		}//
		i = 0;
		while (args[i])//заменить на проход по викиному списку
		{
			args1 = ft_split(args[i], ' ');////
			find_put_status(&mini, &args1);
			mini_push_el(&mini, args1, 0, NULL);
			free_2dim_arr(args1);
			args1 = NULL;
			++i;
		}
		free_2dim_arr(args);
		args = NULL;
		mini.start_el = mini.els;
		execution(&mini);
	}
	return (0);
}
