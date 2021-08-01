/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 16:37:45 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/08/01 18:45:31 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>

typedef struct s_redir
{
	int				r_type;
	char			*file;
	struct s_redir	*next;
	int				heredoc_fds[2];
}	t_redir;

typedef struct s_els
{
	char			**args;
	t_redir			*redir;
	struct s_els	*next;
}	t_els;

typedef struct s_mini
{
	pid_t		pid;
	long long	status;
	char		**envs;
	int			n_els;
	int			n_els_left;
	t_els		*start_el;
	t_els		*els;
	int			in_out_fds[2];
	int			**fd;
	int			cmd_ind;
	char		*echo_n;
	int			fl_echo_n;
}	t_mini;

typedef struct s_help
{
	char	*beg;
	char	*cent;
	char	*endw;
	int		st;
	int		end;
}	t_help;

t_mini				*ret_mini(void);
void				rl_replace_line(const char *text, int clear_undo);
char				**copy_2dim_arr(char **arr);
void				free_2dim_arr(char **arr);
int					count_els_2dim_arr(char **arr);
void				realloc_2dim_arr(t_mini *mini, int size_new);
void				sort_2dim_arr(t_mini *mini, char ***arr);
void				exit_err_malloc_mini(t_mini *mini, char **arr, char *str1);
void				exit_err_pipe_mini(t_mini *mini, char **arr, char *str1);
void				exit_err_malloc(char **arr, char *str1);
void				exit_no_err(t_mini *mini, int ret);
void				free_mini_strct(t_mini *mini, int free_envs,
						int free_echo_n);
void				free_els(t_els *els);
void				free_els_list(t_mini *mini);
void				free_redirs_list(t_mini *mini);
void				free_fds_arr(t_mini *mini);
void				mini_push_el(t_mini *mini, char **args);
int					heredoc_read(t_mini *mini);
t_els				*last_el(t_els *el);
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
int					ft_echo(t_mini *mini, char **args);
int					ft_cd(t_mini *mini);
int					ft_pwd(void);
int					ft_export(t_mini *mini);
int					check_correct_id(char *str);
int					check_char_id(char c, int i);
int					ft_unset(t_mini *mini);
int					ft_env(t_mini *mini);
void				print_envs(char **envs, int uninit);
int					ft_exit(t_mini *mini);
int					cast_status(long long status);
int					exec_bin(t_mini *mini);
void				fork_for_exec_bin_c(t_mini *mini, char *path);
int					exec_bin_pipe(t_mini *mini);
void				exec_cmd_pipe(t_mini *mini);
void				exec_pipe(t_mini *mini);
void				exec_cmd(t_mini *mini);
void				run_chosen_cmd_pipe(t_mini *mini);
void				execution(t_mini *mini);
void				malloc_fds(t_mini *mini, int n_els, int i, int tmp);
void				close_all_fds(t_mini *mini);
void				signal_handler(int sig_num);
void				heredoc_sig_handler(int sig_num);
int					ret_stat_termsig(int ret);
int					exec_redir(t_mini *mini);
int					exec_redir_trunc_out(t_mini *mini, t_redir *red);
int					exec_redir_append_out(t_mini *mini, t_redir *red);
int					exec_redir_in(t_mini *mini, t_redir *red);
void				exec_redir_heredoc(t_redir *red);
void				status_check(t_redir *red);
char				*read_doc(t_mini *mini, t_redir *red);
void				open_envs(t_mini *mini, char **line);
void				free_3_strs(char *s1, char *s2, char *s3);
char				*join_free_parts(t_mini *mini,
						char *s1, char *s2, char *s3);
char				*change_env(t_mini *mini, char *str, int st, int end);

#endif
