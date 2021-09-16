/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_2dim_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:43:06 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/29 18:53:40 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * realloc_2dim_arr function works correctly
 * with a 2 dimensional array
 * only if it is NULL-terminated
**/

static void	dup_element_and_iter(t_mini *mini, char **old_arr, int *i)
{
	mini->envs[*i] = ft_strdup(old_arr[*i]);
	if (!((mini->envs)[*i]))
		exit_err_malloc_mini(mini, old_arr, NULL);
	++(*i);
}

static void	cases_for_realloc(t_mini *mini, char **old_arr,
								int size_new, int size_old)
{
	int	i;

	i = 0;
	if (size_old < size_new)
	{
		while (old_arr[i])
			dup_element_and_iter(mini, old_arr, &i);
		while (i < size_new)
		{
			mini->envs[i] = NULL;
			++i;
		}
	}
	else if (size_old > size_new)
	{
		while (i < size_new)
			dup_element_and_iter(mini, old_arr, &i);
	}
	mini->envs[i] = NULL;
}

void	realloc_2dim_arr(t_mini *mini, int size_new)
{
	int		size_old;
	char	**old_arr;

	size_old = count_els_2dim_arr(mini->envs);
	if (size_old == size_new)
		return ;
	old_arr = copy_2dim_arr(mini->envs);
	free_2dim_arr(mini->envs);
	mini->envs = NULL;
	mini->envs = (char **)malloc(sizeof(char *) * (size_new + 1));
	if (!(mini->envs))
		exit_err_malloc_mini(mini, old_arr, NULL);
	cases_for_realloc(mini, old_arr, size_new, size_old);
	free_2dim_arr(old_arr);
	old_arr = NULL;
}
