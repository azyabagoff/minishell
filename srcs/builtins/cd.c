/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 14:51:03 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/28 20:36:36 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	go_to_path(t_mini *mini, char *path)
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
	tmp = get_env(mini, "PWD");
	set_env(mini, "OLDPWD", tmp);
	free(tmp);
	tmp = NULL;
	tmp = getcwd(NULL, 0);
	set_env(mini, "PWD", tmp);
	free(tmp);
	tmp = NULL;
	return (1);
}

static int	go_home_oldpwd(t_mini *mini, int oldpwd)
{
	char	*tmp;

	if (!oldpwd)
		tmp = get_env(mini, "HOME");
	else
		tmp = get_env(mini, "OLDPWD");
	if (!tmp)
	{
		if (!oldpwd)
			ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		else
			ft_putstr_fd("minishell: cd: OLDPWD not set\n", 1);
		return (0);
	}
	if (!go_to_path(mini, tmp))
	{
		free(tmp);
		tmp = NULL;
		return (0);
	}
	free(tmp);
	tmp = NULL;
	return (1);
}

static int	go_from_home(t_mini *mini, char *arg)
{
	char	*tmp;
	int		i;

	tmp = get_env(mini, "HOME");
	if (!tmp)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 1);
		return (0);
	}
	i = 2;
	tmp = ft__strjoin(tmp, "/");
	if (!tmp)
		exit_err_malloc(mini, NULL, NULL);
	tmp = ft__strjoin(tmp, arg + 2);
	if (!tmp)
		exit_err_malloc(mini, NULL, NULL);
	if (!go_to_path(mini, tmp))
	{
		free(tmp);
		tmp = NULL;
		return (0);
	}
	free(tmp);
	tmp = NULL;
	return (1);
}

static int	cd_cases(t_mini *mini, int flag)
{
	if (!mini->els->args[1] || (mini->els->args[1]
			&& (!ft_strcmp(mini->els->args[1], "~")
				|| !ft_strcmp(mini->els->args[1], "~/")
				|| !ft_strcmp(mini->els->args[1], "--"))))
	{
		flag = 1;
		if (!go_home_oldpwd(mini, 0))
			return (0);
	}
	else if (mini->els->args[1] && !ft_strcmp(mini->els->args[1], "-"))
	{
		flag = 1;
		if (!go_home_oldpwd(mini, 1))
			return (0);
	}
	else if (mini->els->args[1] && !ft_strncmp(mini->els->args[1], "~/", 2)
		&& (int)ft_strlen(mini->els->args[1]) > 2)
	{
		flag = 1;
		if (!go_from_home(mini, mini->els->args[1]))
			return (1);
	}
	return (ft_tern_i((!flag), 1, 2));
}

int	ft_cd(t_mini *mini)
{
	int	ret;

	ret = cd_cases(mini, 0);
	if (!ret)
		return (1);
	else if (ret == 2)
		return (0);
	if (mini->els->args[1] && !ft_strncmp(mini->els->args[1], "-/", 2))
	{
		ft_putstr_fd("minishell: cd: -/: invalid option\n", 1);
		ft_putstr_fd("cd: usage: cd [dir]\n", 1);
		return (1);
	}
	else if (mini->els->args[1] && !ft_strncmp(mini->els->args[1], "--/", 3))
	{
		ft_putstr_fd("minishell: cd: --: invalid option\n", 1);
		ft_putstr_fd("cd: usage: cd [dir]\n", 1);
		return (0);
	}
	else
	{
		if (!go_to_path(mini, mini->els->args[1]))
			return (1);
	}
	return (0);
}
