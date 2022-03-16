/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cut_space(char **str, t_struct *main_struct)
{
	int		i;
	int		len;
	char	*tmp;

	i = 0;
	while (*(*str + i) == ' ')
		i++;
	len = ft_strlen(*str + i);
	tmp = ft_calloc(len + 1, 1);
	if (!tmp)
		not_enough_space(main_struct);
	ft_memcpy(tmp, *str + i, len);
	free(*str);
	*str = tmp;
	return ;
}

int	num_w(char *tmp, int i, int num, int flag_single_q)
{
	int	flag_double_q;

	flag_double_q = 0;
	while (tmp[i])
	{
		if ((tmp[i] == '"') && !flag_double_q)
			flag_double_q = 1;
		else if ((tmp[i] == '"') && flag_double_q)
			flag_double_q = 0;
		else if ((tmp[i] == 39) && !flag_single_q)
			flag_single_q = 1;
		else if ((tmp[i] == 39) && flag_single_q)
			flag_single_q = 0;
		else if ((tmp[i] == ' ') && !flag_single_q && !flag_double_q)
		{
			num++;
			while (tmp[i + 1] == ' ')
			{
				++i;
			}
		}
		i++;
	}
	return (num);
}

void	each_word(char **argument, char **tmp, t_struct *main_struct, int i)
{
	int		flag_single_q;
	int		flag_double_q;
	char	*ptr;

	flag_single_q = 0;
	flag_double_q = 0;
	while (*(*tmp + i))
	{
		check_qoutes(&flag_single_q, &flag_double_q, *tmp, i);
		if ((*(*tmp + i) == ' ') && !flag_single_q && !flag_double_q)
		{
			*argument = ft_substr(*tmp, 0, i);
			if (!*argument)
				not_enough_space(main_struct);
			ptr = ft_strdup(*tmp + i + 1);
			if (!ptr)
				not_enough_space(main_struct);
			free(*tmp);
			*tmp = ptr;
			return ;
		}
		i++;
	}
}

char	**cut_command(char *tmp, t_struct *main_struct)
{
	char	**argument;
	int		num_str;
	int		j;

	num_str = num_w(tmp, 0, 1, 0);
	argument = (char **)malloc(sizeof(char *) * (num_str + 1));
	if (!argument)
		not_enough_space(main_struct);
	j = 0;
	while (--num_str)
	{
		each_word(&argument[j], &tmp, main_struct, 0);
		cut_space(&argument[j], main_struct);
		if (ft_strchr(argument[j], '"') || ft_strchr(argument[j], 39))
			make_a_clear_command(&argument[j], main_struct, 0, 0);
		cut_space(&tmp, main_struct);
		j++;
	}
	argument[j] = tmp;
	if (ft_strchr(argument[j], '"') || ft_strchr(argument[j], 39))
		make_a_clear_command(&argument[j], main_struct, 0, 0);
	j++;
	argument[j] = NULL;
	return (argument);
}
