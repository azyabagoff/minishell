/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 21:50:51 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/06 00:05:42 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ret_stat_termsig(int ret)
{
	if (WTERMSIG(ret) == SIGINT)
	{
		ft_putstr_fd("\n", 2);
		return (130);
	}
	else if (WTERMSIG(ret) == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 2);
		return (131);
	}
	else
		return (ret / 256);
}

void	signal_handler(int sig_num)
{
	int		kill_flag;
	t_mini	*mini;

	mini = ret_mini();
	kill_flag = kill(mini->pid, sig_num);
	if (sig_num == SIGINT && kill_flag)
	{
		mini->fl_echo_n = 0;
		ft_putstr_fd(mini->echo_n, 1);
		if (mini->echo_n)
			free(mini->echo_n);
		mini->echo_n = NULL;
		ft_putstr_fd("minishell > ", 1);
		ft_putstr_fd(rl_line_buffer, 1);
		ft_putstr_fd("  \n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		mini->status = 1;
	}
}
