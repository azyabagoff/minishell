/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_has_val.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 22:11:21 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/15 22:30:52 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_env_has_val(char *env)
{
	int	i;

	i = 0;
	while (env && env[i] && env[i] != '=')
		++i;
	if (i == (int)ft_strlen(env))
		return (0);
	return (1);
}
