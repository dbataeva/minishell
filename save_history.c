/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_previous_history.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_history_for_next_opening(t_struct *main_struct,
char *absolute_path, int fd, char *tmp)
{
	char	*name;

	tmp = ft_strjoin(absolute_path, "/previous_history");
	if (!tmp)
		not_enough_space(main_struct);
	name = ft_strjoin(tmp, g_global_list.shlvl);
	if (!name)
		not_enough_space(main_struct);
	free(tmp);
	fd = open(name, O_WRONLY | O_APPEND);
	if (fd < 0)
	{
		free(name);
		errors_while_opening_or_reading_or_writing(main_struct);
	}
	if ((write(fd, main_struct->line, ft_strlen(main_struct->line)) < 0)
		|| (write(fd, "\n", 1) < 0))
	{
		close(fd);
		free(name);
		errors_while_opening_or_reading_or_writing(main_struct);
	}
	close(fd);
	free(name);
	return ;
}

int	check_numbers_of_strings(int fd, t_struct *main_struct, int n)
{
	char	*ptr;
	char	buf[1024];
	int		rd;

	rd = read(fd, buf, 1023);
	if (rd < 0)
	{
		close(fd);
		errors_while_opening_or_reading_or_writing(main_struct);
	}
	else if (rd == 0)
		return (0);
	while (rd > 0)
	{
		buf[rd] = '\0';
		ptr = ft_strchr(buf, '\n');
		while (ptr)
		{
			ptr++;
			n++;
			ptr = ft_strchr(ptr, '\n');
		}
		rd = read(fd, buf, 1023);
	}
	return (n);
}

void	save_previous_history_conitue(t_struct *main_struct, int fd, char *name)
{
	int		result;
	char	*line;

	result = 1;
	while (result == 1)
	{
		result = get_next_line(fd, &line);
		if (result == -1)
		{
			close(fd);
			free(name);
			not_enough_space(main_struct);
		}
		if ((line[0] != '\0') && (line[0] != ' '))
			add_history(line);
		free(line);
	}
}

void	save_previous_history(t_struct *main_struct)
{
	int		fd;
	char	*name;

	name = ft_strjoin("previous_history", g_global_list.shlvl);
	if (!name)
		not_enough_space(main_struct);
	fd = open(name, O_RDONLY);
	if (fd < 0)
	{
		fd = open(name, O_CREAT | O_RDWR | S_IRWXU);
		if (fd < 0)
		{
			free(name);
			errors_while_opening_or_reading_or_writing(main_struct);
		}
		write(fd, " ", 1);
	}
	save_previous_history_conitue(main_struct, fd, name);
	close(fd);
	free(name);
	return ;
}
