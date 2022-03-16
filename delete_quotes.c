/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_quotes(t_struct *main_struct)
{
	t_minishell_list	*first;
	char				**argument;

	first = main_struct->commands_list;
	while (main_struct->commands_list)
	{
		argument = cut_command(main_struct->commands_list->command,
					main_struct);
		main_struct->commands_list->argument = argument;
		main_struct->commands_list = main_struct->commands_list->next;
	}
	main_struct->commands_list = first;
	return ;
}

void	delete_single_and_double_quotes(int start, int finish, char **command,
t_struct *main_struct)
{
	char	*tmp;
	char	*ptr;
	char	*new_command;
	
	new_command = ft_substr(*command, 0, start);
	if (!new_command)
		not_enough_space(main_struct);
	ptr = ft_substr(*command, start + 1, finish - start - 1);
	if (!ptr)
		ft_free(new_command, NULL, main_struct, 1);
	tmp = ft_strjoin(new_command, ptr);
	ft_free(new_command, ptr, NULL, 0);
	if (!tmp)
		not_enough_space(main_struct);
	ptr = ft_substr(*command, finish + 1, ft_strlen(*command) - finish - 1);
	if (!ptr)
		ft_free(tmp, NULL, main_struct, 1);
	new_command = ft_strjoin(tmp, ptr);
	ft_free(tmp, ptr, NULL, 0);
	if (!new_command)
		not_enough_space(main_struct);
	free(*command);
	*command = new_command;
	return ;
}

void	make_a_clear_command(char **command, t_struct *main_struct,
int flag_single_q, int flag_double_q)
{
	int	start;
	int	i;

	i = 0;
	start = -1;
	while (*(*command + i)) {
		if (check_qoutes(&flag_single_q, &flag_double_q, *command, i))
		{
			if (start == -1)
				start = i;
			else
			{
				delete_single_and_double_quotes(start, i, command, main_struct);
				start = -1;
				i = -1;
			}
		}
		++i;
	}
	return ;
}

int	check_qoutes(int *flag_single_q, int *flag_double_q, char *tmp, int i)
{
	if ((tmp[i] == '"') && !*flag_double_q && !*flag_single_q)
	{
		*flag_double_q = 1;
		return (1);
	}
	else if ((tmp[i] == '"') && *flag_double_q && !*flag_single_q)
	{
		*flag_double_q = 0;
		return (1);
	}		
	else if ((tmp[i] == 39) && !*flag_single_q && !*flag_double_q)
	{
		*flag_single_q = 1;
		return (1);
	}
	else if ((tmp[i] == 39) && *flag_single_q && !*flag_double_q)
	{
		*flag_single_q = 0;
		return (1);
	}
	return (0);
}
