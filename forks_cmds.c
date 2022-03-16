/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_buildin(t_struct *main_struct, int type, int cmd)
{
	if (type == 2)
		cd(main_struct, cmd, 0, NULL);
	else if (type == 3)
		pwd(main_struct, 0, 512);
	else if (type == 4)
		export(main_struct, cmd, 0, NULL);
	else if (type == 6)
		env(main_struct, cmd);
	else if (type == 5)
		unset(main_struct, cmd, 0);
	else if (type == 1)
		echo(main_struct, cmd, 0, 1);
	else if (type == 7)
		exit_from_shell(main_struct, cmd);
}

int	parse_command(t_minishell_list *cmd)
{
	if (ft_strcmp(cmd->argument[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->argument[0], "cd") == 0)
		return (2);
	else if (ft_strcmp(cmd->argument[0], "pwd") == 0)
		return (3);
	else if (ft_strcmp(cmd->argument[0], "export") == 0)
		return (4);
	else if (ft_strcmp(cmd->argument[0], "unset") == 0)
		return (5);
	else if (ft_strcmp(cmd->argument[0], "env") == 0)
		return (6);
	else if (ft_strcmp(cmd->argument[0], "exit") == 0)
		return (7);
	return (0);
}

void	execute_one(t_struct *main_struct, t_minishell_list *cmd, int cmd_num)
{
	int	type;

	type = parse_command(cmd);
	if (!type)
		find_command_in_path(main_struct, 1, cmd_num);
	else
		execute_buildin(main_struct, type, cmd_num);
}

void	execute_cmd(t_struct *main_struct, int type, int cmd_tmp)
{
	if (!main_struct->commands_list)
		return ;
	execute_one(main_struct, main_struct->commands_list, 0);
	(void)type;
	(void)cmd_tmp;
}

void free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		++i;
	}
	free(split);
	return ;
}
