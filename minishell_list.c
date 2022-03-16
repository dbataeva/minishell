/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_list	*ft_minishell_new(char *command, char **argument)
{
	t_minishell_list	*new;

	new = (struct s_minishell_list *)malloc(sizeof(t_minishell_list));
	if (!new)
		return (0);
	new->command = command;
	new->argument = argument;
	new->next = NULL;
	return (new);
}

void	ft_minishell_push_front(t_minishell_list **minishell_list,
t_minishell_list *new)
{
	if (!new)
		return ;
	new->next = (*minishell_list);
	(*minishell_list) = new;
	return ;
}

t_minishell_list	*ft_last_minishell(t_minishell_list *minishell_list)
{
	if (!minishell_list)
		return (NULL);
	while (minishell_list->next)
		minishell_list = minishell_list->next;
	return (minishell_list);
}

void	ft_minishell_push_back(t_minishell_list **minishell_list,
t_minishell_list *new)
{
	t_minishell_list	*last;

	if (!(*minishell_list))
	{
		ft_minishell_push_front(minishell_list, new);
		return ;
	}
	last = ft_last_minishell(*minishell_list);
	last->next = new;
	return ;
}

void	ft_minishell_clear(t_minishell_list **minishell_list)
{
	t_minishell_list	*prev;
	t_minishell_list	*p_next;
	int					i;

	if (!(*minishell_list))
		return ;
	prev = (*minishell_list);
	while (prev)
	{
		i = 0;
		p_next = prev->next;
		if (prev->argument)
		{
			while (prev->argument[i])
				free(prev->argument[i++]);
			free(prev->argument);
		}
		prev->command = NULL;
		prev->argument = NULL;
		free(prev);
		prev = NULL;
		prev = p_next;
	}
	*minishell_list = NULL;
}
