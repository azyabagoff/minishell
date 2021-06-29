/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:59:13 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/29 18:53:01 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*find_cmd_dir(char **dirs, char *cmd)
{
	int				i;
	DIR				*dir;
	struct dirent	*item;

	i = 0;
	dir = NULL;
	while (dirs && dirs[i])
	{
		dir = opendir(dirs[i]);
		if (!dir)
			return (NULL);
		item = readdir(dir);
		while (item)
		{
			if (!ft_strcmp(item->d_name, cmd))
			{
				closedir(dir);
				return (dirs[i]);
			}
			item = readdir(dir);
		}
		closedir(dir);
		++i;
	}
	return (NULL);
}

static int	print_errs_126_127(int num_err, char *path, char **dirs)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(path, 1);
	if (num_err == 1)
	{
		if (!ft_strcmp(strerror(errno), "Not a directory"))
			ft_putendl_fd(": Premission denied", 1);
		else
			ft_putendl_fd(": No such file or directory", 1);
		return (127);
	}
	else if (num_err == 2)
	{
		ft_putendl_fd(": is a directory", 1);
		return (126);
	}
	else if (num_err == 3)
	{
		free_2dim_arr(dirs);
		ft_putstr_fd(": command not found\n", 1);
		return (127);
	}
	return (-1);
}

static int	check_bin_exec(char *path, t_mini *mini)
{
	DIR	*folder;
	int	fd;
	int	ret;

	fd = open(path, O_RDONLY);
	folder = opendir(path);
	ret = 0;
	if (folder != NULL)
	{
		closedir(folder);
		return (print_errs_126_127(2, path, NULL));
	}
	else if (fd == -1 && folder == NULL)
		return (print_errs_126_127(1, path, NULL));
	if (folder)
		closedir(folder);
	close(fd);
	exit_no_err(mini, execve(path, mini->els->args, mini->envs));
	return (0);
}

static int	join_path_to_cmd(t_mini *mini, char **path)
{
	char	*path_env;
	char	**dirs;
	char	*dir;

	path_env = NULL;
	dirs = NULL;
	dir = NULL;
	path_env = get_env_mini(mini, "PATH");
	if (!path_env)
		return (print_errs_126_127(1, mini->els->args[0], NULL));
	dirs = ft_split(path_env, ':');
	if (!dirs)
		exit_err_malloc_mini(mini, NULL, path_env);
	free(path_env);
	dir = find_cmd_dir(dirs, mini->els->args[0]);
	if (!dir)
		return (print_errs_126_127(3, mini->els->args[0], dirs));
	*path = ft_strjoin(dir, "/");
	if (!(*path))
		exit_err_malloc_mini(mini, dirs, NULL);
	free_2dim_arr(dirs);
	*path = ft__strjoin(*path, mini->els->args[0]);
	return (-1);
}

int	exec_bin(t_mini *mini)
{
	char	*path;
	int		check;

	path = NULL;
	check = 0;
	if (ft_strchr(mini->els->args[0], '/') == NULL)
	{
		check = join_path_to_cmd(mini, &path);
		if (check != -1)
			return (check);
		check = check_bin_exec(path, mini);
		if (check)
		{
			free(path);
			return (check);
		}
		free(path);
	}
	else
	{
		check = check_bin_exec(mini->els->args[0], mini);
		if (check)
			return (check);
	}
	return (0);
}
