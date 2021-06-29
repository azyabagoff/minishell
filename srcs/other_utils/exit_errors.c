/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:24:24 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/29 21:08:35 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_err_malloc_mini(t_mini *mini, char **arr, char *str1)
{
	free_mini_strct(mini, 1);
	free_2dim_arr(arr);
	if (str1)
		free(str1);
	ft_putstr_fd("Error.\nMalloc error.\n", 1);
	mini->status = 1;
	exit(1);
}

void	exit_err_pipe_mini(t_mini *mini, char **arr, char *str1)
{
	free_mini_strct(mini, 1);
	free_2dim_arr(arr);
	if (str1)
		free(str1);
	ft_putstr_fd("Error.\nPipe error.\n", 1);
	mini->status = 1;
	exit(1);
}

void	exit_err_malloc(char **arr, char *str1)
{
	free_2dim_arr(arr);
	if (str1)
		free(str1);
	ft_putstr_fd("Error.\nMalloc error.\n", 1);
	exit(1);
}

void	exit_no_err(t_mini *mini, int ret)
{
	free_mini_strct(mini, 1);
	exit(ret);
}
