/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_pwd(char **buf, t_struct *main_struct)
{
	t_env_list	*first;

	first = main_struct->env_list;
	while (main_struct->env_list)
	{
		if (!ft_strncmp(main_struct->env_list->key, "PWD", 4))
		{
			free(main_struct->env_list->essence);
			main_struct->env_list->essence = *buf;
			break ;
		}
		main_struct->env_list = main_struct->env_list->next;
	}
	main_struct->env_list = first;
	return ;
}

char	*find_pwd_in_env(t_struct *main_struct)
{
	t_env_list	*first;
	int			result;

	first = main_struct->env_list;
	result = ft_strncmp("PWD", first->key, 4);
	while (first && result)
	{
		first = first->next;
		result = ft_strncmp("PWD", first->key, 4);
	}
	if (result == 0)
		return (first->essence);
	else
		return (NULL);
}

char	*if_error(t_struct *main_struct, unsigned int memory, int flag)
{
	if (errno == EACCES)
	{
		main_struct->error_list->str_error = "Permission denied";
		g_global_list.exit_status = 1;
		write(2, "minishell: pwd: Permission denied\n", 33);
	}
	else if (errno == ERANGE)
		pwd(main_struct, flag, memory * 2);
	return (NULL);
}

char	*pwd(t_struct *main_struct, int flag, unsigned int memory)
{
	char	*buf;

	buf = (char *)malloc(sizeof(char) * memory);
	if (!buf)
		not_enough_space(main_struct);
	getcwd(buf, memory);
	if (!buf)
		return (if_error(main_struct, memory, flag));
	else if (!flag)
	{
		g_global_list.exit_status = 0;
		main_struct->error_list->str_error = NULL;
		printf("%s\n", buf);
		free(buf);
	}
	else if (flag == 1)
		return (buf);
	else if (flag == 2)
		change_pwd(&buf, main_struct);
	else
		free(buf);
	return (NULL);
}
