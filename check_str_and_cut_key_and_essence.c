/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(t_struct *main_struct) // исправить!!!
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (main_struct->line[i])
	{
		if ((main_struct->line[i] == '"') && !double_quotes && !single_quotes)
			double_quotes = 1;
		else if (main_struct->line[i] == 39 && !single_quotes && !double_quotes)
			single_quotes = 1;
		else if (main_struct->line[i] == '"' && double_quotes && !single_quotes)
			double_quotes = 0;
		else if (main_struct->line[i] == 39 && single_quotes && !double_quotes)
			single_quotes = 0;
		i++;
	}
	if (single_quotes || double_quotes)
		return (1);
	return (0);
}

int	check_str(t_struct *main_struct)
{
	if (!main_struct->line || !main_struct->line[0])
		return (1);
	cut_space(&main_struct->line, main_struct);
	cut_space_in_the_end_of_command(main_struct, &main_struct->line);
	if (check_quotes(main_struct))
	{
		main_struct->error_list->err_num = 130;
		main_struct->error_list->str_error = "syntax error\0";
		main_struct->error_list->exit_status = 2;
		write(2, "minishell: syntax error\n", 24);
		return (1);
	}
	return (0);
}

char	*cut_key(char *argument, t_struct *main_struct)
{
	int		i;
	char	*new;

	i = 0;
	while ((argument[i] != '=') && argument[i])
		i++;
	if (argument[i] == '=')
	{
		if ((i > 0) && (argument[i - 1] == '+'))
			i--;
		new = ft_calloc(i + 1, 1);
		if (!new)
			not_enough_space(main_struct);
		ft_memcpy(new, argument, i);
	}
	else
	{
		new = ft_substr(argument, 0, i);
		if (!new)
			not_enough_space(main_struct);
	}
	return (new);
}

char	*cut_essence(char *argument, t_struct *main_struct)
{
	int		i;
	char	*new;

	i = 0;
	while ((argument[i] != '=') && argument[i])
		i++;
	if (argument[i] == '=')
	{
		i++;
		new = ft_substr(argument, i, ft_strlen(&argument[i]));
		if (!new)
			not_enough_space(main_struct);
	}
	else
		new = NULL;
	return (new);
}
