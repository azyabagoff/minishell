/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sesnowbi <sesnowbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 01:14:57 by sesnowbi          #+#    #+#             */
/*   Updated: 2021/05/19 18:30:05 by sesnowbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *neww)
{
	t_list	*el;

	el = NULL;
	if (lst && neww)
	{
		if (*lst)
		{
			el = ft_lstlast(*lst);
			el->next = neww;
			neww->next = NULL;
		}
		else
		{
			*lst = neww;
			neww->next = NULL;
		}
	}
}
