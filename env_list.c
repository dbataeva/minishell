/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*ft_struct_new(char *key, char *essence)
{
	t_env_list	*env_struct;

	env_struct = (struct s_env_list *)malloc(sizeof(t_env_list));
	if (!env_struct)
		return (0);
	env_struct->key = key;
	env_struct->essence = essence;
	env_struct->next = NULL;
	return (env_struct);
}

void	ft_push_front(t_env_list **env_list, t_env_list *env_new)
{
	if (!env_new)
		return ;
	env_new->next = (*env_list);
	(*env_list) = env_new;
	return ;
}

t_env_list	*ft_last_list(t_env_list *env_list)
{
	if (!env_list)
		return (NULL);
	while (env_list->next)
		env_list = env_list->next;
	return (env_list);
}

void	ft_push_back(t_env_list **env_list, t_env_list *env_new)
{
	t_env_list	*last;

	if (!(*env_list))
	{
		ft_push_front(env_list, env_new);
		return ;
	}
	last = ft_last_list(*env_list);
	last->next = env_new;
	return ;
}

void	ft_list_clear(t_env_list **env_list)
{
	t_env_list	*prev;
	t_env_list	*p_next;

	if (!(*env_list))
		return ;
	prev = (*env_list);
	while (prev)
	{
		p_next = prev->next;
		free(prev->key);
		prev->key = NULL;
		free(prev->essence);
		prev->essence = NULL;
		free(prev);
		prev = NULL;
		prev = p_next;
	}	
	*env_list = NULL;
	return ;
}
