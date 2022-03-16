/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	split_env_list(t_env_list *src, t_env_list **low, t_env_list **high)
{
	t_env_list	*fast;
	t_env_list	*slow;

	fast = NULL;
	slow = NULL;
	if (!src || !src->next)
	{
		(*low) = src;
		(*high) = NULL;
		return ;
	}
	slow = src;
	fast = src->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	(*low) = src;
	(*high) = slow->next;
	slow->next = NULL;
}

void	if_a_or_b(t_env_list *a, t_env_list *b, t_env_list **c)
{
	if (a)
	{
		while (a)
		{
			(*c)->next = a;
			(*c) = (*c)->next;
			a = a->next;
		}
	}
	if (b)
	{
		while (b)
		{
			(*c)->next = b;
			(*c) = (*c)->next;
			b = b->next;
		}
	}
	return ;
}

void	function_body(t_env_list *a, t_env_list *b, t_env_list **c)
{
	while (a && b)
	{
		if (ft_strncmp(a->key, b->key, ft_strlen(b->key) + 1) < 0)
		{
			(*c)->next = a;
			a = a->next;
		}
		else
		{
			(*c)->next = b;
			b = b->next;
		}
		(*c) = (*c)->next;
	}
	if_a_or_b(a, b, c);
	return ;
}

void	concatenate_list(t_env_list *a, t_env_list *b, t_env_list **c)
{
	t_env_list	tmp;

	*c = NULL;
	if (!a || !b)
	{
		if (!a)
			*c = b;
		if (!b)
			*c = a;
		return ;
	}
	if (ft_strncmp(a->key, b->key, ft_strlen(b->key) + 1) < 0)
	{
		*c = a;
		a = a->next;
	}
	else
	{
		*c = b;
		b = b->next;
	}
	tmp.next = *c;
	function_body(a, b, c);
	*c = tmp.next;
	return ;
}

void	sort_env_list(t_env_list **env_list)
{
	t_env_list	*low;
	t_env_list	*high;

	low = NULL;
	high = NULL;
	if ((*env_list == NULL) || ((*env_list)->next == NULL))
		return ;
	split_env_list(*env_list, &low, &high);
	sort_env_list(&low);
	sort_env_list(&high);
	concatenate_list(low, high, env_list);
	return ;
}
