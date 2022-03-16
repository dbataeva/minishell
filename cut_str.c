/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_env(t_struct *main_struct, char *key, int result)
{
	t_env_list	*first;
	char		*essence;

	first = main_struct->env_list;
	result = ft_strncmp(first->key, key, ft_strlen(first->key) + 1);
	while (first->next && result)
	{
		first = first->next;
		result = ft_strncmp(first->key, key, ft_strlen(first->key) + 1);
	}
	if (result == 0)
	{
		essence = ft_strdup(first->essence);
		if (!essence)
			not_enough_space(main_struct);
		return (essence);
	}
	if (!ft_strncmp("?", key, 2))
	{
		essence = ft_itoa(g_global_list.exit_status);
		if (!essence)
			not_enough_space(main_struct);
		return (essence);
	}
	return (NULL);
}

void	change_argument(char **argument, t_struct *main_struct, int i, int j)
{
	char	*key;
	char	*essence;
	char	*new_argument;

	while (*(*argument + i) && (*(*argument + i) != ' ')
		&& (*(*argument + i) != '"'))
		i++;
	if ((*(*argument + i) == '"') || (*(*argument + i) == ' '))
		key = ft_substr(*argument, j + 1, i - j - 1);
	else
		key = ft_substr(*argument, j + 1, i - j + 1);
	if (!key)
		not_enough_space(main_struct);
	essence = find_env(main_struct, key, 0);
	if (!essence)
		new_essence(&essence, key, main_struct);
	new_argument = ft_substr(*argument, 0, j);
	if (!new_argument)
		ft_free(key, essence, main_struct, 1);
	new_key(&key, new_argument, essence, main_struct);
	new_argument = ft_strjoin(key, (*argument + i));
	if (!new_argument)
		ft_free(essence, key, main_struct, 1);
	ft_free(essence, key, *argument, 0);
	*argument = new_argument;
}

void	change_special_characters(char **argument, t_struct *main_struct)
{
	int	flag_single_qoutes;
	int	i;

	i = 0;
	flag_single_qoutes = 0;
	while (*(*argument + i))
	{
		if ((*(*argument + i) == 39) && !flag_single_qoutes)
			flag_single_qoutes = 1;
		else if ((*(*argument + i) == 39) && flag_single_qoutes)
			flag_single_qoutes = 0;
		else if ((*(*argument + i) == '$') && !flag_single_qoutes
			&& (*(*argument + i + 1) != '\0'))
		{
			change_argument(argument, main_struct, i + 1, i);
			cut_space(argument, main_struct);
		}
		i++;
	}
	return ;
}

void	cut_space_in_the_end_of_command(t_struct *main_struct, char **ptr)
{
	int		i;
	char	*tmp;

	i = ft_strlen(*ptr) - 1;
	if (*(*ptr + i) == ' ')
	{
		while (*(*ptr + i) == ' ')
			i--;
		tmp = ft_calloc(i + 2, 1);
		if (!tmp)
			not_enough_space(main_struct);
		ft_memcpy(tmp, *ptr, i + 1);
		free(*ptr);
		*ptr = tmp;
	}
	return ;
}

void	cut_space_in_the_end_in_cmd_list_and_change_special_ch(t_struct
*main_struct)
{
	t_minishell_list	*first;

	first = main_struct->commands_list;
	while (main_struct->commands_list)
	{
		cut_space_in_the_end_of_command(main_struct,
			&main_struct->commands_list->command);
		change_special_characters(&main_struct->commands_list->command,
			main_struct);
		main_struct->commands_list = main_struct->commands_list->next;
	}
	main_struct->commands_list = first;
	return ;
}
