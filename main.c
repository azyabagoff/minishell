/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 20:53:11 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/09/16 23:12:30 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

static void	init_before_loop(t_mini *mini, t_list **list,
								t_list **el_list, char **envp)
{
	*list = NULL;
	*el_list = NULL;
	mini->pid = 1;
	mini->els = NULL;
	mini->envs = copy_2dim_arr(envp);
	change_shlvl(mini);
	del_uninit_envs(mini);
	mini->status = 0;
	mini->n_els = 0;
	mini->n_els_left = 0;
	mini->cmd_ind = 0;
	mini->echo_n = NULL;
}

static void	give_prompt(t_mini *mini, char **line)
{
	if (mini->fl_echo_n == 1)
		mini->fl_echo_n = 2;
	else
		mini->fl_echo_n = 0;
	*line = readline("minishell > ");
	if (!(*line))
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
	if (*line && (*line)[0])
		add_history(*line);
}

static void	parse(t_mini *mini, t_list **list, t_list **el_list, char **line)
{
	*list = parser(*line, mini->envs);
	free(*line);
	*line = NULL;
	*el_list = *list;
	while (*el_list)
	{
		find_put_status(mini, &((t_ret *)((*el_list)->content))->argv);
		mini_push_el(mini, ((t_ret *)((*el_list)->content))->argv,
			((t_ret *)((*el_list)->content))->rdr_list);
		++mini->n_els;
		(*el_list) = (*el_list)->next;
	}
	if (mini->n_els == 0)
		mini->n_els = 1;
}

static void	execute(t_mini *mini)
{
	mini->n_els_left = mini->n_els;
	malloc_fds(mini, mini->n_els, 0, 0);
	mini->in_out_fds[0] = dup(0);
	mini->in_out_fds[1] = dup(1);
	mini->start_el = mini->els;
	execution(mini);
}

int	main(int argc, char *argv[], char *envp[])
{
	char			*line;
	t_mini			*mini;
	t_list			*list;
	t_list			*el_list;

	(void)argc;
	(void)argv;
	line = NULL;
	mini = ret_mini();
	init_before_loop(mini, &list, &el_list, envp);
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		give_prompt(mini, &line);
		parse(mini, &list, &el_list, &line);
		execute(mini);
		free_mini_strct(mini, 0, mini->fl_echo_n);
	}
	return (0);
}
