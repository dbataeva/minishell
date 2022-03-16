/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 16:18:26 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/12 19:36:36 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*prev;
	t_list	*p_next;

	if (((*lst) == NULL) || !del)
		return ;
	prev = (*lst);
	while (prev)
	{
		p_next = prev->next;
		ft_lstdelone(prev, del);
		prev = p_next;
	}
	*lst = NULL;
	return ;
}
