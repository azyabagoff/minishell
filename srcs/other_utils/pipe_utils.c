/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 21:44:46 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/09/14 20:28:37 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	malloc_fds(t_mini *mini, int n_els, int i, int tmp)
{
	mini->fd = (int **)malloc(sizeof(int *) * (n_els - 1));
	if (!mini->fd)
		exit_err_malloc_mini(mini, NULL, NULL);
	while (i < n_els - 1)
	{
		mini->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!mini->fd[i])
		{
			tmp = 0;
			while (tmp < i)
			{
				free(mini->fd[tmp]);
				++tmp;
			}
			free(mini->fd);
			mini->fd = NULL;
			exit_err_malloc_mini(mini, NULL, NULL);
		}
		mini->fd[i][0] = -1;
		mini->fd[i][1] = -1;
		++i;
	}
}

void	close_all_fds(t_mini *mini)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < mini->n_els - 1)
	{
		j = 0;
		while (j < 2)
		{
			close(mini->fd[i][j]);
			++j;
		}
		++i;
	}
}
