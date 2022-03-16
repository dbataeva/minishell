/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	free(lst);
	return ;
}

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

void	del_content_lst(void *line)
{
	free(line);
	line = NULL;
	return ;
}

void	quit(t_struct *main_struct, unsigned char status)
{
	if (main_struct->env_list)
		ft_list_clear(&main_struct->env_list);
	ft_lstclear(&main_struct->history_list, &del_content_lst);
	ft_minishell_clear(&main_struct->commands_list);
	if (main_struct->error_list)
		free(main_struct->error_list);
	rl_clear_history();
	exit(status);
}
