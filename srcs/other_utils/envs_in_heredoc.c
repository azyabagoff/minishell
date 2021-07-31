/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_in_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:46:40 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/30 16:53:46 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	put_st_end_env(char *str, int *st, int *end, int *i)
{
	int	j;

	j = 0;
	*st = *i;
	++(*i);
	while (str[*i] && str[*i] != ' ' && check_char_id(str[*i], j))
	{
		++j;
		++(*i);
	}
	*end = *i;
}

void	free_3_strs(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

char	*join_free_parts(t_mini *mini, char *s1, char *s2, char *s3)
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

static void	open_envs_cicle(t_mini *mini, int *flag, char **str)
{
	int	i;
	int	st;
	int	end;

	i = 0;
	st = 0;
	end = 0;
	while (*str && (*str)[i] && i < (int)ft_strlen(*str))
	{
		*flag = 0;
		if ((*str)[i] == '$' && (*str)[i + 1] && (*str)[i + 1] != ' ')
		{
			*flag = 1;
			put_st_end_env(*str, &st, &end, &i);
			*str = change_env(mini, *str, st, end);
			break ;
		}
		++i;
	}
}

void	open_envs(t_mini *mini, char **line)
{
	char	*str;
	int		flag;

	str = *line;
	*line = NULL;
	flag = 1;
	while (flag == 1)
	{
		flag = 0;
		open_envs_cicle(mini, &flag, &str);
	}
	*line = str;
}
