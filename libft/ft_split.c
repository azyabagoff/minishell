/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 16:02:41 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/04/14 18:00:00 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_free_spl(char **split, size_t wnum)
{
	size_t	i;

	i = 0;
	while (i < wnum)
	{
		free(split[i]);
		++i;
	}
	free(split);
}

static char	**ft_alloc_spl(char const *s, char c, size_t *wnum, size_t s_len)
{
	char	**split;
	size_t	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != c && ((s[i + 1] && s[i + 1] == c) || i == s_len - 1))
			++(*wnum);
		++i;
	}
	split = (char **)malloc(sizeof(s) * (*wnum + 1));
	if (!split)
		return (NULL);
	split[*wnum] = NULL;
	return (split);
}

static char	**ft_spl(char const *s, char c, char **split, size_t s_len)
{
	size_t	i;
	size_t	j;
	size_t	beg;
	size_t	end;

	i = -1;
	j = 0;
	beg = 0;
	end = 0;
	while (s[++i])
	{
		if (s[i] != c && (i == 0 || (s[i - 1] && (s[i - 1] == c))))
			beg = i;
		if (s[i] != c && (i == s_len - 1 || (s[i + 1] && s[i + 1] == c)))
		{
			end = i;
			split[j] = ft_substr(s, beg, end - beg + 1);
			if (!split[j++])
			{
				ft_free_spl(split, j - 1);
				return (NULL);
			}
		}
	}
	return (split);
}

static char	**ft_handle_sl_0(char **splitted, const char *s)
{
	splitted = (char **)malloc(sizeof(s) * 2);
	if (!splitted)
		return (NULL);
	splitted[0] = ft_strdup(s);
	if (!splitted[0])
	{
		ft_free_spl(splitted, 1);
		return (NULL);
	}
	splitted[1] = NULL;
	return (splitted);
}

char	**ft_split(char const *s, char c)
{
	char	**splitted;
	size_t	wnum;
	size_t	s_len;

	if (!s)
		return (NULL);
	splitted = NULL;
	if (c == '\0')
		return (ft_handle_sl_0(splitted, s));
	wnum = 0;
	s_len = ft_strlen(s);
	splitted = ft_alloc_spl(s, c, &wnum, s_len);
	if (!splitted)
		return (NULL);
	splitted = ft_spl(s, c, splitted, s_len);
	if (!splitted)
		return (NULL);
	return (splitted);
}
