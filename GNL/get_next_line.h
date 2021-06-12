/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 17:44:27 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/02/10 22:19:22 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <unistd.h>
# include <stdlib.h>

int			get_next_line(int fd, char **line);
int			ft__strlen(const char *s);
char		*ft__strjoin(char *s1, char *s2);
char		*ft_cut_after_endl(char *tmp);
char		*ft_cut_before_endl(char *tmp);

#endif
