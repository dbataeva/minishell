/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cchromos <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 15:22:39 by cchromos          #+#    #+#             */
/*   Updated: 2021/09/07 15:35:21 by cchromos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"

typedef struct s_global_list
{
	int		shell_in_shell;
	int		exit_status;
	char	*shlvl;
}				t_global_list;

t_global_list	g_global_list;

typedef struct s_env_list
{
	char				*key;
	char				*essence;
	struct s_env_list	*next;
}				t_env_list;

typedef struct s_minishell_list
{
	char					*command;
	char					**argument;
	struct s_minishell_list	*next;
}				t_minishell_list;

typedef struct s_error_list
{
	int						err_num;
	int						exit_status;
	char					*str_error;
}				t_error_list;

typedef struct s_struct
{
	char				*line;
	char				*prompt;
	char				**old_commands;
	int					ctrl_d;
	t_list				*history_list;
	t_minishell_list	*commands_list;
	t_env_list			*env_list;
	t_error_list		*error_list;
}				t_struct;

int					main(int argc, char **argv, char **env);
t_env_list			*ft_struct_new(char *key, char *essence);
void				ft_push_back(t_env_list **env_list, t_env_list *env_new);
void				ft_list_clear(t_env_list **env_list);
void				cut_space(char **str, t_struct *main_struct);
void				not_enough_space(t_struct *main_struct);
void				quit(t_struct *main_struct, unsigned char status);
void				del_content_lst(void *line);
int					check_str(t_struct *main_struct);
void				ft_minishell_clear(t_minishell_list **minishell_list);
void				ft_minishell_push_back(t_minishell_list **minishell_list,
						t_minishell_list *new);
t_minishell_list	*ft_minishell_new(char *command, char **argument);
void				cut_space_in_the_end_in_cmd_list_and_change_special_ch(
						t_struct *main_struct);
void				sort_env_list(t_env_list **env_list);
void				make_a_clear_command(char **command, t_struct *main_struct,
					int flag_single_q, int flag_double_q);
void				delete_quotes(t_struct *main_struct);
char				*pwd(t_struct *main_struct, int flag, unsigned int memory);
void				cd(t_struct *main_struct, int cmd, int result,
						char *oldpwd);
void				env(t_struct *main_struct, int cmd);
void				push_middle(int i, t_struct *main_struct, t_env_list *new);
void				export(t_struct *main_struct, int cmd, int i, char *key);
void				unset(t_struct *main_struct, int cmd, int j);
void				del_env_list(int i, t_struct *main_struct);
void				ft_push_front(t_env_list **env_list, t_env_list *env_new);
void				echo(t_struct *main_struct, int cmd, int n_flag, int i);
int					env_list_size(t_env_list *env_list);
int					exec(t_struct *main_struct, int flag, int cmd, int status);
void				change_special_characters(char **argument,
						t_struct *main_struct);
char				**cut_command(char *tmp, t_struct *main_struct);
int					try_exec_without_path(t_struct *main_struct, int cmd);
void				find_command_in_path(t_struct *main_struct, int exec_flag,
						int cmd);
void				cut_space_in_the_end_of_command(t_struct *main_struct,
						char **ptr);
int					check_qoutes(int *flag_single_q, int *flag_double_q,
						char *tmp, int i);
void				errors_while_opening_or_reading_or_writing(t_struct
						*main_struct);
void				save_previous_history(t_struct *main_struct);
void				save_history_for_next_opening(t_struct *main_struct,
						char *absolute_path, int fd, char *tmp);
void				ft_free(char *str1, char *str2, void *main_struct,
						int flag);
void				new_essence(char **essence, char *key,
						t_struct *main_struct);
void				new_key(char **key, char *new_argument, char *essence,
						t_struct *main_struct);
void				exit_from_shell(t_struct *main_struct, int cmd);
void				if_daughter(int sig);
void				if_parent(int sig);
char				*cut_essence(char *argument, t_struct *main_struct);
char				*cut_key(char *argument, t_struct *main_struct);
void				execute_cmd(t_struct *main_struct, int type, int cmd_tmp);
int					ft_strcmp(const char *s1, const char *s2);
void				if_command_not_found(t_struct *main_struct, int cmd);
void				if_exec_flag(t_struct *main_struct);
void				main_loop(t_struct *main_struct, int exec_flag,
						char *absolute_path);
int					make_wait(pid_t *pid, int *status, char **envp,
						t_struct *main_struct);
void				do_exec(t_struct *main_struct, int cmd, char **envp);
void				copy_envp(char **envp, t_struct *main_struct, int i);
void				free_copy_env(char **envp, t_struct *main_struct, int flag);

t_minishell_list	*find_cmd(t_struct *main_strcut, int i);
void				get_status(int status);
void				free_split(char **split);

void				new_prompt(void);

#endif