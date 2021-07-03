/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:37:45 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/01 16:11:30 by sesnowbi         ###   ########.fr       */
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
# include <signal.h>

pid_t		g_pid;

typedef struct s_els
{
	char			**args;
	int				redir_type;
	char			*file;
	struct s_els	*next;
}	t_els;

typedef struct s_mini
{
	char		**envs;
	int			n_els;
	int			n_els_left;
	t_els		*start_el;
	t_els		*els;
	int			**fd;
	int			cmd_ind;
	long long	status;
}	t_mini;

char				**copy_2dim_arr(char **arr);
void				free_2dim_arr(char **arr);
int					count_els_2dim_arr(char **arr);
void				realloc_2dim_arr(t_mini *mini, int size_new);
void				sort_2dim_arr(t_mini *mini, char ***arr);
void				exit_err_malloc_mini(t_mini *mini, char **arr, char *str1);
void				exit_err_pipe_mini(t_mini *mini, char **arr, char *str1);
void				exit_err_malloc(char **arr, char *str1);
void				exit_no_err(t_mini *mini, int ret);
void				free_mini_strct(t_mini *mini, int free_envs);
void				free_els(t_els *els);
void				free_els_list(t_mini *mini);
void				free_fds_arr(t_mini *mini);
void				mini_push_el(t_mini *mini, char **args,
						int redir_type, char *file);
void				find_put_status(t_mini *mini, char ***args);
void				change_shlvl(t_mini *mini);
char				*get_env_mini(t_mini *mini, char *name);
char				*get_env(char **envs, char *name);
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
int					exec_bin_pipe(t_mini *mini);
void				exec_cmd_pipe(t_mini *mini);
void				exec_pipe(t_mini *mini);
void				exec_cmd(t_mini *mini);
void				run_chosen_cmd_pipe(t_mini *mini);
void				execution(t_mini *mini);
void				malloc_fds(t_mini *mini, int n_els, int i, int tmp);
void				close_all_fds(t_mini *mini);
int					exec_redir(t_mini *mini);

#endif
