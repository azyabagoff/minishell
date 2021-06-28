/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:37:45 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/06/28 21:47:04 by sesnowbi         ###   ########.fr       */
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

pid_t		g_pid;

// add redir to t_els

typedef struct s_els
{
	char			**args;
	struct s_els	*next;
}	t_els;

typedef struct s_mini
{
	char		**envs;
	t_els		*start_el;
	t_els		*els;
	long long	status;
}	t_mini;

char				**copy_2dim_arr(char **arr);
void				free_2dim_arr(char **arr);
int					count_els_2dim_arr(char **arr);
void				realloc_2dim_arr(t_mini *mini, int size_new);
void				sort_2dim_arr(t_mini *mini, char ***arr);
void				exit_err_malloc(t_mini *mini, char **arr, char *str1);
void				exit_no_err(t_mini *mini, int ret);
void				free_mini_strct(t_mini *mini, int free_envs);
void				free_els_list(t_mini *mini);
char				*get_env(t_mini *mini, char *name);
char				*get_env_name(t_mini *mini, char *env);
int					check_env_has_val(char *env);
int					check_env_exists(t_mini *mini, char *name);
void				set_env(t_mini *mini, char *name, char *value);
void				del_env_by_name(t_mini *mini, char *name);
void				del_uninit_envs(t_mini *mini);
int					ft_echo(char **args);
int					ft_cd(t_mini *mini);
int					ft_pwd(void);
int					ft_export(t_mini *mini);
int					check_correct_id(char *str);
int					ft_unset(t_mini *mini);
int					ft_env(t_mini *mini);
void				print_envs(char **envs, int uninit);
int					ft_exit(t_mini *mini);
int					cast_status(long long status);
int					exec_bin(t_mini *mini);
void				exec_cmd(t_mini *mini);
void				execution(t_mini *mini);
///
void				mini_push_el(t_mini *mini, char **args);
t_els				*last_el(t_els *el);
///

#endif
