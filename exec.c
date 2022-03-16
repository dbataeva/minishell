/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	try_exec_without_path(t_struct *main_struct, int cmd)
{
	struct stat			buf[4096];
	t_minishell_list	*tmp;

	tmp = find_cmd(main_struct, cmd);
	if (!tmp)
		return (1);
	if (!stat(tmp->argument[0], buf))
	{
		exec(main_struct, 1, cmd, -1);
		return (0);
	}
	return (1);
}

void	free_copy_env(char **envp, t_struct *main_struct, int flag)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
	if (!flag)
		return ;
	else
		not_enough_space(main_struct);
	return ;
}

void	check_minishell_and_change_signals(t_struct *main_struct, pid_t	*pid)
{
	if (ft_strrchr(main_struct->commands_list->argument[0], 'm'))
	{
		if (!ft_strncmp("minishell",
				ft_strrchr(main_struct->commands_list->argument[0], 'm'), 10)) 
		{
			signal(SIGINT, SIG_IGN);
			signal(SIGQUIT, SIG_IGN);
			g_global_list.shell_in_shell = 2;
		}
		else
		{
			signal(SIGINT, if_daughter);
			signal(SIGQUIT, if_daughter);
		}
	}
	else
	{
		signal(SIGINT, if_daughter);
		signal(SIGQUIT, if_daughter);
	}
	*pid = fork();
	return ;
}

int	exec(t_struct *main_struct, int flag, int cmd, int status)
{
	pid_t	pid;
	char	**envp;
	int		i;

	i = env_list_size(main_struct->env_list);
	envp = (char **)malloc(sizeof(char *) * (i + 1));
	if (!envp)
		not_enough_space(main_struct);
	copy_envp(envp, main_struct, i);
	check_minishell_and_change_signals(main_struct, &pid);
	if (pid == -1)
	{
		free_copy_env(envp, main_struct, 0);
		main_struct->error_list->err_num = 1;
		main_struct->error_list->str_error = strerror(errno);
		not_enough_space(main_struct);
	}
	if (pid == 0)
		do_exec(main_struct, cmd, envp);
	if (make_wait(&pid, &status, envp, main_struct) != -1)
		return (status);
	free_copy_env(envp, main_struct, 0);
	if (flag == 0)
		quit(main_struct, 1);
	return (status);
}
