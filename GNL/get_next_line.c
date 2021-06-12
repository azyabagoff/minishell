/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:43:25 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/04/14 16:44:29 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_tern_gnl_i(int cond, int ret_true, int ret_false)
{
	if (cond)
		return (ret_true);
	else
		return (ret_false);
}

static int	ft_safe_free(char *str, char *buf, int ret)
{
	if (str)
		free(str);
	if (buf)
		free(buf);
	return (ret);
}

static int	ft_endl_search(char *str, int *ptr)
{
	if (!str)
		return (1);
	while (str[*ptr])
	{
		if (str[*ptr] == '\n')
			return (0);
		++(*ptr);
	}
	return (1);
}

static int	ft_prev_checks(char **buf, char **line, int fd, int *ptr)
{
	*buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!(*buf))
		return (0);
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (0);
	*ptr = 0;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	static char		*str;
	char			*buf;
	int				r;
	int				ptr;

	if (!ft_prev_checks(&buf, line, fd, &ptr))
		return (ft_safe_free(str, buf, -1));
	r = 1;
	while (r > 0 && ft_endl_search(str, &ptr))
	{
		r = read(fd, buf, BUFFER_SIZE);
		if (r == -1)
			return (ft_safe_free(str, buf, -1));
		buf[r] = '\0';
		str = ft__strjoin(str, buf);
		if (!str)
			return (ft_safe_free(str, buf, -1));
	}
	free(buf);
	*line = ft_cut_after_endl(str);
	if (!(*line))
		return (-1);
	str = ft_cut_before_endl(str);
	return (ft_tern_gnl_i((r == 0), 0, 1));
}
