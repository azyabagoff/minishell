/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_2dim_arr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 19:43:06 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/16 13:52:30 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * realloc_2dim_arr function works correctly
 * with a 2 dimensional array
 * only if it is NULL-terminated
**/

static void	dup_element_and_iter(char ***arr, char **old_arr, int *i)
{
	(*arr)[*i] = ft_strdup(old_arr[*i]);
	if (!((*arr)[*i]))
		exit_err_malloc();
	++(*i);
}

static void	cases_for_realloc(char ***arr, char **old_arr,
								int size_new, int size_old)
{
	int	i;

	i = 0;
	if (size_old < size_new)
	{
		while (old_arr[i])
			dup_element_and_iter(arr, old_arr, &i);
		while (i < size_new)
		{
			(*arr)[i] = NULL;
			++i;
		}
	}
	else if (size_old > size_new)
	{
		while (i < size_new)
			dup_element_and_iter(arr, old_arr, &i);
	}
	(*arr)[i] = NULL;
}

void	realloc_2dim_arr(char ***arr, int size_new)
{
	int		size_old;
	char	**old_arr;

	size_old = count_els_2dim_arr(*arr);
	if (size_old == size_new)
		return ;
	old_arr = copy_2dim_arr(*arr);
	free_2dim_arr(*arr);
	*arr = NULL;
	*arr = (char **)malloc(sizeof(char *) * (size_new + 1));
	if (!(*arr))
		exit_err_malloc();
	cases_for_realloc(arr, old_arr, size_new, size_old);
	free_2dim_arr(old_arr);
	old_arr = NULL;
}
