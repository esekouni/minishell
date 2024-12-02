# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aouchaad <aouchaad@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/12 17:28:35 by aouchaad          #+#    #+#              #
#    Updated: 2023/06/23 16:08:46 by aouchaad         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	minishell.c \
				utils1.c \
				utils2.c \
				utils3.c \
				giga_splite.c \
				environment_path.c \
				syntax_error_checker.c \
				expantion.c \
				expantion2.c \
				expantion3.c \
				cotes_terminator.c \
				tokens_counter.c \
				syntax_error_cases.c \
				tokens_identifier.c \
				create_liste.c \
				export.c \
				export2.c \
				export3.c \
				unset.c \
				create_export.c \
				echo.c \
				env.c \
				ft_split.c \
				command_path.c \
				ft_sssstrjoin.c \
				here_doc.c \
				names_generator.c \
				ft_itoa.c \
				ft_strdup.c \
				split_afexp.c \
				path_error.c \
				cd.c \
				pwd.c \
				ambiguous_redirect.c \
				exit.c \
				ft_putstr_fd.c \
				print_error.c \
				check_exist_and_permission.c \
				check_exist_and_permission_inchild.c \
				join_args_and_envp.c \
				command_path2.c \
				here_doc2.c \
				tokens_identifier2.c \
				free_functions.c \
				utils5.c \
				the_executer.c \
				non_builtins.c \
				non_builtins2.c \
				expantion4.c \
				utils_4.c \
				remplace_space_nonprint.c \
				expantion_anbiguous.c \
				ft_atoi.c \
				minishell2.c
				
OBJS		=	${SRCS:.c=.o}

NAME		=	minishell

CC			=	cc

RLD		=	-lreadline -L/goinfre/aouchaad/brew/opt/readline/lib


CFLAGS		=	-Wall -Wextra -Werror
				

RM			=	rm -rf

all : ${NAME}

%.o : %.c
		${CC} ${CFLAGS} -I/goinfre/aouchaad/brew/opt/readline/include -c $< -o $@

${NAME} : ${OBJS} minishell.h
		${CC} ${CFLAGS} ${OBJS} ${RLD} -o $@

clean :
	${RM} ${OBJS}
	clear

fclean : clean
	${RM} ${NAME}
	clear

re : fclean all
	clear