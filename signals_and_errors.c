/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_prompt(void)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;

}

void	if_daughter(int sig)
{
	if (g_global_list.shell_in_shell != 2)
	{
		if (sig == SIGINT)
			write(2, "\n", 1);
		if (sig == SIGQUIT)
			write(2, "Quit: 3\n", 8);
	}
	return ;
}

void	if_parent(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		ft_putstr_fd("  \n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_global_list.shell_in_shell = 1;
		g_global_list.exit_status = 130;
	}
	return ;
}

void	not_enough_space(t_struct *main_struct)
{
	main_struct->error_list->err_num = 12;
	main_struct->error_list->str_error = "minishell: not_enough_space\0";
	quit(main_struct, 1);
	return ;
}

void	errors_while_opening_or_reading_or_writing(t_struct *main_struct)
{
	main_struct->error_list->err_num = errno;
	main_struct->error_list->str_error = strerror(errno);
	printf("minishell: %s\n", main_struct->error_list->str_error);
	quit(main_struct, 1);
	return ;
}
