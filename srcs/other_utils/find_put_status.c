/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_put_status.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:32:20 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/05 20:22:42 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_put_status(t_mini *mini, char ***args)//добавить в аргументы викину структуру
{
	int	j;

	j = 0;
	while (*args && (*args)[j])
	{
		if (!ft_strcmp((*args)[j], "$?"))
		{
			free((*args)[j]);
			(*args)[j] = ft_strdup(ft_lltoa(mini->status));
			if (!(*args)[j])
			{
				//очистка викиной структуры
				exit_err_malloc_mini(mini, NULL, NULL);
			}
		}
		++j;
	}
}
