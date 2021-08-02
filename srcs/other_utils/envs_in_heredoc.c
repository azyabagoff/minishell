/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_in_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 20:46:40 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/08/02 12:46:08 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_3_strs(char *s1, char *s2, char *s3)
{
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	if (s3)
		free(s3);
}

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
