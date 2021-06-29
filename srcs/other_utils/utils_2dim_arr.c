/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2dim_arr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:18:56 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/29 19:17:19 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_2dim_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr && arr[i])
	{
		free(arr[i]);
		++i;
	}
	free(arr);
}

int	count_els_2dim_arr(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr && arr[i])
		++i;
	return (i);
}

char	**copy_2dim_arr(char **arr)
{
	char	**cp_arr;
	int		i;

	cp_arr = NULL;
	i = 0;
	while (arr && arr[i])
		++i;
	cp_arr = (char **)malloc(sizeof(char *) * (i + 1));
	if (!cp_arr)
	{
		ft_putstr_fd("Error.\nMalloc error.\n", 1);
		exit(1);
	}
	i = 0;
	while (arr && arr[i])
	{
		cp_arr[i] = ft_strdup(arr[i]);
		++i;
	}
	cp_arr[i] = NULL;
	return (cp_arr);
}

static void	swap_strings(t_mini *mini, char ***arr, int i, int j)
{
	char	*tmp_str;

	tmp_str = ft_strdup((*arr)[i]);
	if (!tmp_str)
		exit_err_malloc_mini(mini, NULL, NULL);
	free((*arr)[i]);
	(*arr)[i] = NULL;
	(*arr)[i] = ft_strdup((*arr)[j]);
	if (!(*arr)[i])
		exit_err_malloc_mini(mini, NULL, tmp_str);
	free((*arr)[j]);
	(*arr)[j] = NULL;
	(*arr)[j] = ft_strdup(tmp_str);
	if (!(*arr)[j])
		exit_err_malloc_mini(mini, NULL, tmp_str);
	free(tmp_str);
	tmp_str = NULL;
}

void	sort_2dim_arr(t_mini *mini, char ***arr)
{
	int		i;
	int		j;
	int		size;

	i = 0;
	j = 0;
	if (!(*arr))
		return ;
	size = count_els_2dim_arr((*arr));
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp((*arr)[i], (*arr)[j]) > 0)
				swap_strings(mini, arr, i, j);
			++j;
		}
		++i;
	}
}
