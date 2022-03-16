/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	i = 0;
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

t_minishell_list	*find_cmd(t_struct *main_strcut, int i)
{
	t_minishell_list	*tmp;
	int					n;

	n = 0;
	tmp = main_strcut->commands_list;
	while (tmp && n != i)
	{
		n++;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	return (tmp);
}

void	if_command_not_found(t_struct *main_struct, int cmd)
{
	main_struct->error_list->exit_status = 127;
	main_struct->error_list->str_error = "command not found";
	write(2, "minishell: ", 11);
	write(2, find_cmd(main_struct, cmd)->argument[0],
		ft_strlen(find_cmd(main_struct, cmd)->argument[0]));
	write(2, ": ", 2);
	write(2, main_struct->error_list->str_error,
		ft_strlen(main_struct->error_list->str_error));
	write(2, "\n", 1);
}


void	new_essence(char **essence, char *key, t_struct *main_struct)
{
	*essence = ft_calloc(1, 1);
	if (!*essence)
		ft_free(key, NULL, main_struct, 1);
	return ;
}

void	new_key(char **key, char *new_argument, char *essence,
t_struct *main_struct)
{
	free(*key);
	*key = ft_strjoin(new_argument, essence);
	if (!*key)
		ft_free(essence, new_argument, main_struct, 1);
	free(new_argument);
	return ;
}
