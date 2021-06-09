# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rlinkov <rlinkov@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/28 17:09:16 by rlinkov           #+#    #+#              #
#    Updated: 2021/06/09 18:25:39 by rlinkov          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= minishell

CC 			:=	gcc
CFLAGS	 	:=	-Wall -Wextra -Werror
RM 			:=	/bin/rm -f

LIBFT		:= ./libft/libft.a

INCLUDE 	:= 	-Iinclude/

SRCS		:=	main.c \
				./src/clean_cmd.c \
				./src/code_cmd.c \
				./src/code_cmd_2.c \
				./src/code_cmd_3.c \
				./src/error.c \
				./src/prompt.c \
				./src/syntaxe_cmd.c \
				./src/exec.c \
				./src/builtin_functions.c \
				./src/builtin_functions_helper.c \
				./src/struct_init.c \
				./src/copy_env.c \
				./src/set_env_var.c \
				./src/debug.c \
				./src/free_functions.c \
				./src/io_redirection.c \
				./src/handle_pipe.c \
				./src/utilities_1.c \
				./src/utilities_2.c \
				./src/export.c \
				./src/export_bis.c \
				./src/unset.c \
				./src/signals.c \

OBJ			:=	$(SRCS:%.c=%.o)

all			:	$(NAME)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE)

$(NAME)		:	$(OBJ) $(LIBFT)
	@ $(CC) $(CFLAGS) $(INCLUDE) $(SRCS) -o $(NAME) $(LIBFT)

$(LIBFT)	:
	@ $(MAKE) -C ./libft

make run	: all
	./minishell

clean		:
	@ $(RM) $(OBJ)
	@ $(MAKE) -C ./libft clean

fclean		:	clean
	@ $(RM) minishell
	@ $(MAKE) -C ./libft fclean

re			: fclean all

.PHONY		: all clean fclean remake
