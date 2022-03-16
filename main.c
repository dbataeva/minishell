/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_env_list(char *key, char *essence, t_struct *main_struct)
{
	t_env_list	*env_new;

	env_new = ft_struct_new(key, essence);
	if (!env_new)
		not_enough_space(main_struct);
	ft_push_back(&main_struct->env_list, env_new);
	return ;
}

void	copy_env(char **env, t_struct *main_struct)
{
	int			i;
	int			j;
	char		*key;
	char		*essence;

	i = 0;
	while (env[i])
	{
		j = 0;
		{
			while (env[i][j] && (env[i][j] != '='))
				j++;
			key = ft_calloc(j + 1, 1);
			if (!key)
				not_enough_space(main_struct);
			ft_memcpy(key, env[i], j);
			essence = ft_calloc(ft_strlen(&env[i][j]), 1);
			if (!essence)
				not_enough_space(main_struct);
			ft_memcpy(essence, &env[i][j + 1], ft_strlen(&env[i][j + 1]));
			make_env_list(key, essence, main_struct);
		}
		i++;
	}
	sort_env_list(&main_struct->env_list);
}

void	init_structs(t_struct *main_struct)
{
	t_error_list	*error_list;	

	main_struct->line = NULL;
	main_struct->prompt = "minishell$ ";
	main_struct->env_list = NULL;
	main_struct->history_list = NULL;
	main_struct->commands_list = NULL;
	error_list = (struct s_error_list *)malloc(sizeof(t_error_list));
	if (!error_list)
		not_enough_space(main_struct);
	error_list->err_num = -1;
	error_list->str_error = NULL;
	error_list->exit_status = 0;
	main_struct->error_list = error_list;
	main_struct->commands_list = NULL;
}

void	change_shlvl(t_struct *main_struct)
{
	int			old_shlvl;
	int			result;
	t_env_list	*first;

	first = main_struct->env_list;
	result = ft_strncmp(first->key, "SHLVL", 6);
	while (first->next && (result != 0))
	{
		first = first->next;
		result = ft_strncmp(first->key, "SHLVL", 6);
	}
	if (result == 0)
	{
		old_shlvl = ft_atoi(first->essence) + 1;
		free(first->essence);
		first->essence = ft_itoa(old_shlvl);
		if (!first->essence)
			not_enough_space(main_struct);
		g_global_list.shlvl = first->essence;
	}
	return ;
}

int	main(int argc, char **argv, char **env)
{
	t_struct		main_struct;
	int				exec_flag;
	char			*absolute_path;

	init_structs(&main_struct);
	exec_flag = 1;
	main_struct.ctrl_d = 0;
	if (argc != 1)
		exec_flag = 0;
	copy_env(env, &main_struct);
	change_shlvl(&main_struct);
	absolute_path = pwd(&main_struct, 1, 512);
	save_previous_history(&main_struct);
	g_global_list.shell_in_shell = 0;
	signal(SIGINT, if_parent);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		if (exec_flag)
			if_exec_flag(&main_struct);
		else
			main_struct.line = ft_strdup(argv[1]);
		main_loop(&main_struct, exec_flag, absolute_path);
	}
	return (0);
}
