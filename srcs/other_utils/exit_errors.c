/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:24:24 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/21 14:09:16 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_err_malloc(char **arr, char *str1)
{
	free_2dim_arr(arr);
	if (str1)
		free(str1);
	ft_putstr_fd("Error.\nMalloc error.\n", 1);
	g_status = 1;
	exit(1);
}
