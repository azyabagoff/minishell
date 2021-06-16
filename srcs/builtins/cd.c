/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:51:03 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/16 23:21:19 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	go_to_path(char ***envs, char *path)
{
	char	*tmp;

	tmp = NULL;
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(tmp, 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(strerror(errno), 1);
		return (0);
	}
	tmp = get_env(*envs, "PWD");
	set_env(envs, "OLDPWD", tmp);
	free(tmp);
	tmp = NULL;
	tmp = getcwd(NULL, 0);
	set_env(envs, "PWD", tmp);
	free(tmp);
	tmp = NULL;
	return (1);
}

static int	go_home(char ***envs)
{
	char	*tmp;

	tmp = get_env(*envs, "HOME");
	if (!go_to_path(envs, tmp))
	{
		free(tmp);
		tmp = NULL;
		return (0);
	}
	free(tmp);
	tmp = NULL;
	return (1);
}

int	ft_cd(char ***envs, char **args)
{
	if (!args[1] || (args[1] && (!ft_strcmp(args[1], "~")
				|| !ft_strcmp(args[1], "~/") || !ft_strcmp(args[1], "--"))))
		if (!go_home(envs))
			return (1);
	printf("pwd = %s\n", getcwd(NULL, 0));///
	printf("PWD = %s\n", get_env(*envs, "PWD"));///
	printf("OLDPWD = %s\n", get_env(*envs, "OLDPWD"));///
	return (0);
}
