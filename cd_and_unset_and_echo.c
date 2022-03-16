/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(t_struct *main_struct, int cmd, int n_flag, int i) // echo "$USER" неправильно работает
{
	t_minishell_list	*tmp;

	tmp = find_cmd(main_struct, cmd);
	g_global_list.exit_status = 0;
	if (!tmp->argument[1])
	{
		printf("\n");
		return ;
	}
	if (!ft_strncmp("-n", tmp->argument[i], 3))
	{
		i++;
		n_flag = 1;
	}
	if (!tmp->argument[i] && n_flag)
		return ;
	while (tmp->argument[i])
	{
		printf("%s", tmp->argument[i++]);
		if (tmp->argument[i])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	main_struct->error_list->str_error = NULL;
}

void	unset(t_struct *main_struct, int cmd, int j)
{
	t_env_list			*first;
	int					result;
	int					i;
	t_minishell_list	*tmp;

	tmp = find_cmd(main_struct, cmd);
	while (tmp->argument[j])
	{
		first = main_struct->env_list;
		i = 0;
		result = ft_strncmp(first->key, tmp->argument[j],
				ft_strlen(first->key) + 1);
		while ((result != 0) && first->next)
		{
			first = first->next;
			result = ft_strncmp(first->key, tmp->argument[j],
					ft_strlen(first->key) + 1);
			i++;
		}
		if (result == 0)
			del_env_list(i, main_struct);
		j++;
	}
	main_struct->error_list->str_error = NULL;
	g_global_list.exit_status = 0;
}

void	old_pwd(char **buf, t_struct *main_struct, int i)
{
	t_env_list	*first;
	int			result;
	t_env_list	*new;

	first = main_struct->env_list;
	result = ft_strncmp(first->key, "OLDPWD", 7);
	while ((result < 0) && first)
	{
		first = first->next;
		result = ft_strncmp(first->key, "OLDPWD", 7);
		i++;
	}
	if (result == 0)
	{
		free(first->essence);
		first->essence = *buf;
	}
	else
	{
		new = ft_struct_new("OLDPWD", *buf);
		if (!new)
			not_enough_space(main_struct);
		push_middle(i, main_struct, new);
	}
}

void	chdir_error(t_struct *main_struct)
{
	g_global_list.exit_status = 1;
	main_struct->error_list->str_error = strerror(errno);
	write(2, "minishell: cd: ", 15);
	write(2, main_struct->commands_list->argument[1],
		ft_strlen(main_struct->commands_list->argument[1]));
	write(2, " ", 1);
	write(2, main_struct->error_list->str_error,
		ft_strlen(main_struct->error_list->str_error));
	write(2, "\n", 1);
}

void	cd(t_struct *main_struct, int cmd, int result, char *oldpwd)
{
	t_minishell_list	*tmp;

	tmp = find_cmd(main_struct, cmd);
	oldpwd = pwd(main_struct, 1, 512);
	if (!tmp->argument[1])
	{
		write(2, "minishell: syntax error\n", 24);
		g_global_list.exit_status = 2;
		return ;
	}
	result = chdir(tmp->argument[1]);
	if (result != 0)
	{
		chdir_error(main_struct);
		free(oldpwd);
	}
	else
	{
		main_struct->error_list->exit_status = 0;
		main_struct->error_list->str_error = NULL;
		old_pwd(&oldpwd, main_struct, 0);
		pwd(main_struct, 2, 512);
	}
	return ;
}
