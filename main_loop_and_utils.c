/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop_and_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_command(t_struct *main_struct)
{
	t_minishell_list	*commands_list;

	commands_list = ft_minishell_new(main_struct->line, NULL);
	if (!commands_list)
		not_enough_space(main_struct);
	ft_minishell_push_back(&main_struct->commands_list, commands_list);
	return ;
}

void	change_register(t_struct *main_struct)
{
	int					i;
	int					j;
	t_minishell_list	*first;

	first = main_struct->commands_list;
	while (first)
	{
		i = 0;
		j = 0;
		if (first->argument[i])
		{
			while (first->argument[i][j])
			{
				first->argument[i][j] = ft_tolower(first->argument[i][j]);
				j++;
			}
		}
		first = first->next;
	}
	return ;
}

void	ft_free(char *str1, char *str2, void *main_struct, int flag)
{
	if (str1)
		free(str1);
	if (str2)
		free(str2);
	if (flag)
		not_enough_space(main_struct);
	else if (main_struct)
		free(main_struct);
	return ;
}

void	if_exec_flag(t_struct *main_struct)
{
	main_struct->line = readline(main_struct->prompt);
	if (!main_struct->line)
	{
		main_struct->line = ft_strdup("exit");
		printf("exit\n");
		main_struct->ctrl_d = 1;
	}
	return ;
}

void	main_loop(t_struct *main_struct, int exec_flag, char *absolute_path)
{
	if (!main_struct->line)
		not_enough_space(main_struct);
	if ((main_struct->line[0] != '\0') && exec_flag && !main_struct->ctrl_d)
	{
		add_history(main_struct->line);
		save_history_for_next_opening(main_struct, absolute_path, 0, NULL);
	}
	if (!check_str(main_struct))
	{
		save_command(main_struct);
		cut_space_in_the_end_in_cmd_list_and_change_special_ch(main_struct);
		delete_quotes(main_struct);
		change_register(main_struct);
		execute_cmd(main_struct, 0, 0);
		ft_minishell_clear(&main_struct->commands_list);
	}
	else
		free(main_struct->line);
	return ;
}
