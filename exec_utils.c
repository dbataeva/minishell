/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_envp(char **envp, t_struct *main_struct, int i)
{
	int			j;
	char		*ptr;
	char		*tmp;
	t_env_list	*first;

	first = main_struct->env_list;
	j = 0;
	while (j < i)
	{
		tmp = ft_strjoin(first->key, "=");
		if (!tmp)
			free_copy_env(envp, main_struct, 1);
		ptr = ft_strjoin(tmp, first->essence);
		if (!ptr)
		{
			free(tmp);
			free_copy_env(envp, main_struct, 1);
		}
		free(tmp);
		envp[j] = ptr;
		j++;
		first = first->next;
	}
	envp[j] = NULL;
	return ;
}

void	if_error_execve(t_struct *main_struct)
{
	main_struct->error_list->err_num = errno;
	main_struct->error_list->str_error = strerror(errno);
	write(2, "minishell: ", 11);
	write(2, main_struct->commands_list->argument[0],
		ft_strlen(main_struct->commands_list->argument[0]));
	write(2, ": ", 2);
	write(2, main_struct->error_list->str_error,
		ft_strlen(main_struct->error_list->str_error));
	write(2, "\n", 1);
	return ;
}

void	do_exec(t_struct *main_struct, int cmd, char **envp)
{
	t_minishell_list	*tmp;

	tmp = find_cmd(main_struct, cmd);
	if (execve(tmp->argument[0], tmp->argument, envp) == -1)
		if_error_execve(main_struct);
	return ;
}

void	get_status(int status)
{
	if (WIFEXITED(status))
		g_global_list.exit_status = WEXITSTATUS(status);
	else
	{
		if (WIFSIGNALED(status))
			g_global_list.exit_status = 128 + WTERMSIG(status);
	}
	return ;
}

int	make_wait(pid_t *pid, int *status, char **envp, t_struct *main_struct)
{
	*pid = wait(status);
	if (g_global_list.shell_in_shell == 2)
		g_global_list.shell_in_shell = 0;
	signal(SIGINT, if_parent);
	signal(SIGQUIT, SIG_IGN);
	if (*pid == -1)
	{
		free_copy_env(envp, main_struct, 0);
		main_struct->error_list->err_num = 1;
		main_struct->error_list->str_error = strerror(errno);
		return (*status);
	}
	get_status(*status);
	return (-1);
}
