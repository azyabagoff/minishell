/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:37:45 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/25 22:57:06 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../GNL/get_next_line.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

long long	g_status;
pid_t		g_pid;

char				**copy_2dim_arr(char **arr);
void				free_2dim_arr(char **arr);
int					count_els_2dim_arr(char **arr);
void				realloc_2dim_arr(char ***arr, int size_new);
void				sort_2dim_arr(char ***arr);
void				exit_err_malloc(char **arr, char *str1);
void				exit_no_err(int ret);
char				*get_env(char **envs, char *name);
char				*get_env_name(char *env);
int					check_env_has_val(char *env);
int					check_env_exists(char **envs, char *name);
void				set_env(char ***envs, char *name, char *value);
void				del_env_by_name(char ***envs, char *name);
void				del_uninit_envs(char ***envs);
int					ft_echo(char **args);
int					ft_cd(char ***envs, char **args);
int					ft_pwd(void);
int					ft_export(char ***envs, char **args);
int					check_correct_id(char *str);
int					ft_unset(char ***envs, char **args);
int					ft_env(char **envs, char **args);
void				print_envs(char **envs, int uninit);
int					ft_exit(char ***envs, char ***args);
int					cast_status(long long status);
int					exec_bin(char **args, char **envs);

#endif
