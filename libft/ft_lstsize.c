/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 00:50:23 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/04/14 17:04:29 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*ptr;

	size = 0;
	ptr = NULL;
	if (lst)
	{
		ptr = lst;
		while (ptr->next)
		{
			ptr = ptr->next;
			++size;
		}
		return (++size);
	}
	return (0);
}
