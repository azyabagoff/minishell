/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 08:36:33 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/07/07 12:23:32 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	int		a_fd;
	int		b_fd;
	int		c_fd;

	(void)argc;
	a_fd = open("../a", O_RDONLY);
	dup2(a_fd, 0);
	close(a_fd);
	b_fd = open("../b", O_RDONLY);
	dup2(b_fd, 0);
	close(b_fd);
	c_fd = open("../c", O_WRONLY | O_TRUNC);
	dup2(c_fd, 1);
	close(c_fd);
	a_fd = open("../a", O_WRONLY | O_TRUNC);
	dup2(a_fd, 1);
	close(a_fd);
	execve("/bin/cat", argv, envp);
	return (0);
}
