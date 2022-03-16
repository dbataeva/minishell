/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	miltiple_arguments(t_struct *main_struct, int i, t_minishell_list *cmd)
{	
	while (cmd->argument[1][i] && ft_isdigit(cmd->argument[1][i]))
		i++;
	if (cmd->argument[1][i] == '\0')
	{
		write(2, "exit\nminishell: exit: too many arguments\n", 41);
		main_struct->error_list->exit_status = 1;
	}
	else
	{
		write(2, "exit\nminishell: exit: ", 22);
		write(2, main_struct->commands_list->argument[1],
			ft_strlen(main_struct->commands_list->argument[1]));
		write(2, " numeric argument required\n", 27);
		quit(main_struct, 2);
	}
	return ;
}

void	one_argument(t_struct *main_struct, int i, int status,
t_minishell_list *cmd)
{
	while (cmd->argument[1][i] && ft_isdigit(cmd->argument[1][i]))
		i++;
	if (cmd->argument[1][i] == '\0')
		quit(main_struct, status);
	else
	{
		write(2, "exit\nminishell: exit: ", 22);
		write(2, main_struct->commands_list->argument[1],
			ft_strlen(main_struct->commands_list->argument[1]));
		write(2, " numeric argument required\n", 27);
		quit(main_struct, 2);
	}
	return ;
}

void	exit_from_shell(t_struct *main_struct, int cmd)
{
	int					i;
	int					status;
	t_minishell_list	*tmp;

	tmp = find_cmd(main_struct, cmd);
	if (!tmp->argument[1])
	{
		if (!main_struct->ctrl_d)
			printf("exit\n");
		quit(main_struct, g_global_list.exit_status);
	}
	status = ft_atoi(tmp->argument[1]);
	i = 0;
	if ((tmp->argument[1][i] == '-') || (tmp->argument[1][i] == '+'))
		i++;
	if (tmp->argument[1] && tmp->argument[2])
		miltiple_arguments(main_struct, i, tmp);
	else
		one_argument(main_struct, i, status, tmp);
	return ;
}

void	env(t_struct *main_struct, int cmd)
{
	t_env_list			*first;
	t_minishell_list	*tmp;

	tmp = find_cmd(main_struct, cmd);
	if (tmp->argument[1])
	{
		write(2, "minishell: syntax error\n", 24);
		main_struct->error_list->exit_status = 2;
		return ;
	}
	if (!main_struct->env_list)
		return ;
	first = main_struct->env_list;
	while (main_struct->env_list)
	{
		if (main_struct->env_list->essence)
			printf("%s=%s\n", main_struct->env_list->key,
				main_struct->env_list->essence);
		main_struct->env_list = main_struct->env_list->next;
	}
	main_struct->env_list = first;
	g_global_list.exit_status = 0;
	main_struct->error_list->str_error = NULL;
	return ;
}

