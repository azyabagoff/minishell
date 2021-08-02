/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_in_heredoc_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:36:20 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/08/02 12:42:20 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	set_beg_part(char *str, t_help *help, int *malloc_err_flag)
{
	if (help->st != 0)
	{
		help->beg = ft_substr(str, 0, help->st);
		if (!help->beg)
			*malloc_err_flag = 1;
	}
}

static void	set_cent_part(t_mini *mini, char *str,
							t_help *help, int *malloc_err_flag)
{
	if (!check_char_id(str[help->end], help->end - help->st - 1)
		&& check_char_id(str[help->end - 1], help->end - help->st - 1))
	{
		help->endw = ft_substr(str, help->st + 1, help->end - help->st - 1);
		if (!help->endw)
			*malloc_err_flag = 1;
		help->cent = get_env_mini(mini, help->endw);
		if (!help->cent)
			help->cent = ft_strdup("\0");
		if (!help->cent)
			*malloc_err_flag = 1;
		free(help->endw);
		help->endw = NULL;
	}
	else if (!check_char_id(str[help->end], 0) && str[help->end - 1] == '$')
	{
		++help->end;
		help->cent = ft_strdup("\0");
		if (!help->cent)
			*malloc_err_flag = 1;
	}
}

static void	set_endw_part_free(t_mini *mini, char *str,
							t_help *help, int *malloc_err_flag)
{
	if (help->end != (int)ft_strlen(str))
	{
		help->endw = ft_substr(str, help->end, ft_strlen(str) - help->end);
		if (!help->endw)
			*malloc_err_flag = 1;
	}
	if (*malloc_err_flag == 1)
	{
		free_3_strs(help->beg, help->cent, help->endw);
		exit_err_malloc_mini(mini, NULL, str);
	}
	free(str);
}

static char	*join_free_parts(t_mini *mini, char *s1, char *s2, char *s3)
{
	char	*ret;
	int		malloc_err_flag;

	ret = NULL;
	malloc_err_flag = 0;
	if (s1)
	{
		ret = ft_strjoin(s1, s2);
		malloc_err_flag = ft_tern_i((!ret), 1, 0);
	}
	else if (s2)
	{
		ret = ft_strdup(s2);
		malloc_err_flag = ft_tern_i((!ret), 1, 0);
	}
	if (ret || s3)
	{
		ret = ft_strjoin1(ret, s3);
		malloc_err_flag = ft_tern_i((!ret), 1, 0);
	}
	free_3_strs(s1, s2, s3);
	if (malloc_err_flag == 1)
		exit_err_malloc_mini(mini, NULL, NULL);
	return (ret);
}

char	*change_env(t_mini *mini, char *str, int st, int end)
{
	t_help	help;
	int		malloc_err_flag;

	help.beg = NULL;
	help.cent = NULL;
	help.endw = NULL;
	help.st = st;
	help.end = end;
	malloc_err_flag = 0;
	set_beg_part(str, &help, &malloc_err_flag);
	if (str[help.end] == '?' && str[help.end - 1] == '$')
	{
		++help.end;
		help.cent = ft_itoa(cast_status(mini->status));
		if (!help.cent)
			malloc_err_flag = 1;
	}
	else
		set_cent_part(mini, str, &help, &malloc_err_flag);
	set_endw_part_free(mini, str, &help, &malloc_err_flag);
	return (join_free_parts(mini, help.beg, help.cent, help.endw));
}
