/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_argument(char **argument, t_struct *main_struct, int i, char *tmp)
{
	if (ft_isdigit(*(*argument + i)))
		return (1);
	while (*(*argument + i) && (*(*argument + i) != '=')
		&& (ft_isalnum(*(*argument + i)) || (*(*argument + i) == '_')))
		i++;
	if (*(*argument + i) == '\0')
		return (0);
	if (*(*argument + i) == '+')
		i++;
	if (*(*argument + i) == '=')
	{
		i++;
		if ((!*(*argument + i) && !i) || (*(*argument + i) == '='))
			return (1);
		if (*(*argument + i) == ' ')
		{
			tmp = ft_substr(*argument, 0, i);
			if (!tmp)
				not_enough_space(main_struct);
			free(*argument);
			*argument = tmp;
		}
		return (0);
	}
	return (1);
}

void	find_the_place(t_struct *main_struct, char *key, char *essence, int i)
{
	int			result;
	t_env_list	*first;
	t_env_list	*new;

	first = main_struct->env_list;
	result = ft_strncmp(first->key, key, ft_strlen(first->key) + 1);
	while ((result < 0) && first->next)
	{
		first = first->next;
		result = ft_strncmp(first->key, key, ft_strlen(first->key) + 1);
		i++;
	}
	if (result == 0)
	{
		free(first->essence);
		first->essence = essence;
		free(key);
	}
	else
	{
		new = ft_struct_new(key, essence);
		if (!new)
			not_enough_space(main_struct);
		push_middle(--i, main_struct, new);
	}
}

void	do_declare(t_struct *main_struct)
{
	t_env_list	*first;

	first = main_struct->env_list;
	while (first)
	{
		if (ft_strncmp(first->key, "_", 2))
		{
			printf("declare -x %s", first->key);
			if (first->essence)
				printf("=\"%s\"", first->essence);
			printf("\n");
		}
		first = first->next;
	}
	return ;
}

void	if_error_export(t_struct *main_struct, int i)
{
	main_struct->error_list->str_error = "not a valid identifier";
	g_global_list.exit_status = 1;
	write(2, "minishell: export: `", 20);
	write(2, main_struct->commands_list->argument[i],
		ft_strlen(main_struct->commands_list->argument[i]));
	write(2, "\': ", 3);
	write(2, main_struct->error_list->str_error,
		ft_strlen(main_struct->error_list->str_error));
	write(2, "\n", 1);
	return ;
}

void	export(t_struct *main_struct, int cmd, int i, char *key)
{
	char				*essence;
	t_minishell_list	*tmp;

	tmp = find_cmd(main_struct, cmd);
	if (!tmp->argument[1])
		do_declare(main_struct);
	while (tmp->argument[++i])
	{
		if (check_argument(&tmp->argument[i], main_struct, 0, NULL))
			if_error_export(main_struct, i);
		else
		{
			key = cut_key(tmp->argument[i], main_struct);
			essence = cut_essence(tmp->argument[i], main_struct);
			find_the_place(main_struct, key, essence, 0);
			main_struct->error_list->str_error = NULL;
			g_global_list.exit_status = 0;
		}
	}
	return ;
}
