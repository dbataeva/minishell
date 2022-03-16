/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 19:29:35 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/13 19:35:06 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*start;

	if (!lst)
		return (ft_lstnew(NULL));
	lst_new = ft_lstnew(lst->content);
	if (!lst_new)
		return (NULL);
	start = lst_new;
	lst_new->content = f(lst_new->content);
	lst = lst->next;
	while (lst)
	{
		lst_new = ft_lstnew(lst->content);
		if (!lst_new)
		{
			ft_lstclear(&start, del);
			return (NULL);
		}
		lst_new->content = f(lst_new->content);
		ft_lstadd_back(&start, lst_new);
		lst = lst->next;
	}
	return (start);
}
