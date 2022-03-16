/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:22:09 by cchromos          #+#    #+#             */
/*   Updated: 2020/11/12 13:34:19 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*elem;

	elem = (struct s_list *)malloc(sizeof(t_list));
	if (elem == NULL)
		return (0);
	else
	{
		elem->content = content;
		elem->next = NULL;
	}
	return (elem);
}
