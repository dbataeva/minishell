NAME	=	minishell

SRCS	=	cd_and_unset_and_echo.c \
			check_str_and_cut_key_and_essence.c \
			cut_command.c \
			cut_str.c \
			delete_quotes.c \
			env_list_utils.c \
			env_list.c \
			exec_utils.c \
			exec.c \
			exit_and_env.c \
			export.c \
			find_command_in_path.c \
			forks_cmds.c \
			main_loop_and_utils.c \
			main.c \
			minishell_list.c \
			pwd.c \
			quit.c \
			save_history.c \
			signals_and_errors.c \
			sort_env_list.c \
			utils.c \
			get_next_line/get_next_line.c \

OBJS	=	$(SRCS:%.c=%.o)

CC		=	gcc

FLAGS	=	-Wall -Wextra -Werror -o

RM		=	rm -f

all:		${NAME}

${NAME}:	${OBJS} minishell.h
			cd libft && make
			${CC} ${FLAGS} ${NAME} ${OBJS} libft/libft.a  -lreadline

clean:
			cd libft && make clean
			${RM} ${OBJS}

fclean:		clean
			cd libft && make fclean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re