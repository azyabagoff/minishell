/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:51:03 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/21 14:11:26 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	go_to_path(char ***envs, char *path)
{
	char	*tmp;

	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 1);
		ft_putstr_fd(path, 1);
		ft_putstr_fd(": ", 1);
		ft_putstr_fd(strerror(errno), 1);
		ft_putstr_fd("\n", 1);
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

static int	go_home_oldpwd(char ***envs, int oldpwd)
{
	char	*tmp;

	if (!oldpwd)
		tmp = get_env(*envs, "HOME");
	else
		tmp = get_env(*envs, "OLDPWD");
	if (!tmp)
	{
		if (!oldpwd)
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		else
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 1);
		return (0);
	}
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

static int	go_from_home(char ***envs, char *arg)
{
	char	*tmp;
	int		i;

	tmp = get_env(*envs, "HOME");
	if (!tmp)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		return (0);
	}
	i = 2;
	tmp = ft__strjoin(tmp, "/");
	if (!tmp)
		exit_err_malloc(NULL, NULL);
	tmp = ft__strjoin(tmp, arg + 2);
	if (!tmp)
		exit_err_malloc(NULL, NULL);
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

static int	cd_cases(char ***envs, char **args)
{
	int	flag;

	flag = 0;
	if (!args[1] || (args[1] && (!ft_strcmp(args[1], "~")
				|| !ft_strcmp(args[1], "~/") || !ft_strcmp(args[1], "--"))))
	{
		flag = 1;
		if (!go_home_oldpwd(envs, 0))
			return (0);
	}
	else if (args[1] && !ft_strcmp(args[1], "-"))
	{
		flag = 1;
		if (!go_home_oldpwd(envs, 1))
			return (0);
	}
	else if (args[1] && !ft_strncmp(args[1], "~/", 2)
		&& (int)ft_strlen(args[1]) > 2)
	{
		flag = 1;
		if (!go_from_home(envs, args[1]))
			return (1);
	}
	return (ft_tern_i((!flag), 1, 2));
}

int	ft_cd(char ***envs, char **args)
{
	int	ret;

	ret = cd_cases(envs, args);
	if (!ret)
		return (1);
	else if (ret == 2)
		return (0);
	if (args[1] && !ft_strncmp(args[1], "-/", 2))
	{
		ft_putstr_fd("minishell: cd: -/: invalid option\n", 1);
		ft_putstr_fd("cd: usage: cd [dir]\n", 1);
		return (1);
	}
	else if (args[1] && !ft_strncmp(args[1], "--/", 3))
	{
		ft_putstr_fd("minishell: cd: --: invalid option\n", 1);
		ft_putstr_fd("cd: usage: cd [dir]\n", 1);
		return (0);
	}
	else
	{
		if (!go_to_path(envs, args[1]))
			return (1);
	}
	return (0);
}
