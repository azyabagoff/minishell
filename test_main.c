/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 20:53:11 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/28 21:58:11 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

///

t_els	*last_el(t_els *el)
{
	if (el)
	{
		while (el->next)
			el = el->next;
		return (el);
	}
	return (NULL);
}

void	mini_push_el(t_mini *mini, char **args)
{
	t_els	*el;
	t_els	*neww;

	el = NULL;
	neww = (t_els *)malloc(sizeof(t_els));
	neww->args = copy_2dim_arr(args);
	neww->next = NULL;
	if (mini->els)
	{
		el = last_el(mini->els);
		el->next = neww;
		neww->next = NULL;
	}
	else
	{
		mini->els = neww;
		neww->next = NULL;
	}
}
///

int	main(int argc, char *argv[], char *envp[])
{
	char		*line;
	char		**args;
	char		**args1;
	int			i;
	t_mini		mini;

	(void)argc;
	(void)argv;
	mini.els = NULL;
	args = NULL;
	args1 = NULL;
	line = NULL;
	i = 0;
	mini.envs = copy_2dim_arr(envp);
	while (1)
	{
		line = readline("minishell > ");
		if (line && line[0])
			add_history(line);
		args = ft_split(line, '|');
		free(line);
		line = NULL;
		if (!args)
			continue ;
		if (!args[0])
		{
			free(args);
			continue ;
		}
		i = 0;
		while (args[i])
		{
			args1 = ft_split(args[i], ' ');
			mini_push_el(&mini, args1);
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
