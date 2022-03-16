/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_command_in_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_path(t_env_list *env_list)
{
	int			result;
	t_env_list	*first;

	first = env_list;
	result = ft_strncmp(first->key, "PATH", 5);
	while (result && first->next)
	{
		first = first->next;
		result = ft_strncmp(first->key, "PATH", 5);
	}
	if (!result)
		return (first->essence);
	return (NULL);
}

char	*make_new_path(t_struct *main_struct, char *path_i, int cmd,
t_minishell_list **found_cmd)
{
	char	*tmp;
	char	*ptr;

	tmp = ft_strjoin(path_i, "/");
	if (!tmp)
		not_enough_space(main_struct);
	*found_cmd = find_cmd(main_struct, cmd);
	if (!*found_cmd)
		return (NULL);
	ptr = ft_strjoin(tmp, (*found_cmd)->argument[0]);
	free(tmp);
	if (!ptr)
		not_enough_space(main_struct);
	return (ptr);
}

int	find_the_command(char **path, t_struct *main_struct, int exec_flag, int cmd)
{
	int					i;
	char				*ptr;
	struct stat			buf[4096];
	t_minishell_list	*found_cmd;

	i = 0;
	while (path[i])
	{
		ptr = make_new_path(main_struct, path[i], cmd, &found_cmd);
		if (!stat(ptr, buf))
		{
			free(found_cmd->argument[0]);
			found_cmd->argument[0] = ptr;
			exec(main_struct, exec_flag, cmd, -1);
			return (0);
		}
		free(ptr);
		i++;
	}
	return (1);
}

void	if_no_path(t_struct *main_struct, int cmd)
{
	main_struct->error_list->str_error = "No such file or directory";
	main_struct->error_list->exit_status = 127;
	write(2, "minishell: ", 12);
	write(2, find_cmd(main_struct, cmd)->command,
		ft_strlen(find_cmd(main_struct, cmd)->command));
	write(2, ": ", 2);
	write(2, main_struct->error_list->str_error,
		ft_strlen(main_struct->error_list->str_error));
	write(2, "\n", 1);
	return ;
}

void	find_command_in_path(t_struct *main_struct, int exec_flag, int cmd)
{
	char	**split;
	char	*path;
	char	*old_command;

	old_command = ft_strdup(main_struct->commands_list->argument[0]);
	path = get_path(main_struct->env_list);
	if (!path)
	{
		if_no_path(main_struct, cmd);
		return ;
	}
	split = ft_split(path, ':');
	if (!split)
		not_enough_space(main_struct);
	if (find_the_command(split, main_struct, exec_flag, cmd))
	{
		free(main_struct->commands_list->argument[0]);
		main_struct->commands_list->argument[0] = old_command;
		if (try_exec_without_path(main_struct, cmd))
			if_command_not_found(main_struct, cmd);
	}
	else
		free(old_command);
	free_split(split);
	return ;
}
