/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_middle(int i, t_struct *main_struct, t_env_list *new)
{
	t_env_list	*first;

	if (i == 0)
	{
		ft_push_front(&main_struct->env_list, new);
		return ;
	}
	first = main_struct->env_list;
	while (i)
	{
		main_struct->env_list = main_struct->env_list->next;
		i--;
	}
	new->next = main_struct->env_list->next;
	main_struct->env_list->next = new;
	main_struct->env_list = first;
	return ;
}

void	del_first(t_struct *main_struct)
{
	t_env_list	*ptr;

	ptr = main_struct->env_list->next;
	free(main_struct->env_list->essence);
	free(main_struct->env_list->key);
	free(main_struct->env_list);
	main_struct->env_list = ptr;
	return ;
}

void	del_env_list(int i, t_struct *main_struct)
{
	t_env_list	*first;
	t_env_list	*prev;
	t_env_list	*ptr;

	if (i == 0)
	{
		del_first(main_struct);
		return ;
	}
	first = main_struct->env_list;
	i--;
	while (i)
	{
		first = first->next;
		i--;
	}
	prev = first;
	first = first->next;
	ptr = first->next;
	prev->next = ptr;
	free(first->key);
	free(first->essence);
	free(first);
	return ;
}

int	env_list_size(t_env_list *env_list)
{
	int			i;
	t_env_list	*first;

	i = 0;
	first = env_list;
	while (first)
	{
		first = first->next;
		i++;
	}
	return (i);
}
