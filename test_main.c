/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 20:53:11 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/16 16:58:08 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	char			**args;
	char			**args1;
	t_mini			*mini;
	int				i;

	(void)argc;
	(void)argv;
	mini = ret_mini();
	mini->pid = 1;
	mini->els = NULL;
	args = NULL;
	args1 = NULL;
	line = NULL;
	i = 0;
	mini->envs = copy_2dim_arr(envp);
	change_shlvl(mini);
	del_uninit_envs(mini);
	mini->status = 0;
	mini->n_els = 0;
	mini->n_els_left = 0;
	mini->cmd_ind = 0;
	mini->echo_n = NULL;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (mini->fl_echo_n == 1)
			mini->fl_echo_n = 2;
		else
			mini->fl_echo_n = 0;
		line = readline("minishell > ");//
		if (!line)//добавить в викину часть парсинга и очищать ее структуру при необходимости
		{
			mini->fl_echo_n = 0;
			ft_putstr_fd("\033[A", 1);
			ft_putstr_fd(mini->echo_n, 1);
			if (mini->echo_n)
				free(mini->echo_n);
			mini->echo_n = NULL;
			ft_putstr_fd("minishell > exit\n", 1);
			exit_no_err(mini, mini->status);
		}
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
			find_put_status(mini, &args1);
			mini_push_el(mini, args1);//добавить в функцию инициализацию редиректов
			++mini->n_els;
			free_2dim_arr(args1);
			args1 = NULL;
			++i;
		}
		mini->n_els_left = mini->n_els;
		free_2dim_arr(args);//заменить на очистку викиной структуры
		args = NULL;
		malloc_fds(mini, mini->n_els, 0, 0);
		mini->in_out_fds[0] = dup(0);
		mini->in_out_fds[1] = dup(1);
		mini->start_el = mini->els;
		execution(mini);
		free_mini_strct(mini, 0, mini->fl_echo_n);//добавить в функцию очистку редиректов
	}
	return (0);
}
